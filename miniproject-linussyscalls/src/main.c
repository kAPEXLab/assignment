#include "roles.h"
#include "ipc_mq.h"
#include "ipc_shm.h"
#include "ipc_fifo.h"
#include "signals.h"

static void usage(const char *argv0) {
    fprintf(stderr,
      "Usage:\n"
      "  %s [--producers N] [--duration SEC] [--rate HZ] [--seed SEED]\n"
      "  Roles:\n"
      "    --role=supervisor (default)\n"
      "    --role=aggregator --producers N\n"
      "    --role=producer --id ID --duration SEC --rate HZ --seed SEED\n",
      argv0);
}

int main(int argc, char **argv) {
    const char *role = "supervisor";
    int producers = 2, duration = 10, rate = 10, id = 0;
    unsigned seed = (unsigned)time(NULL);

    for (int i = 1; i < argc; ++i) {
        if (!strncmp(argv[i], "--role=", 7)) role = argv[i] + 7;
        else if (!strncmp(argv[i], "--producers=", 12)) producers = atoi(argv[i] + 12);
        else if (!strncmp(argv[i], "--duration=", 11)) duration = atoi(argv[i] + 11);
        else if (!strncmp(argv[i], "--rate=", 7)) rate = atoi(argv[i] + 7);
        else if (!strncmp(argv[i], "--seed=", 7)) seed = (unsigned)atoi(argv[i] + 7);
        else if (!strncmp(argv[i], "--id=", 5)) id = atoi(argv[i] + 5);
        else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) { usage(argv[0]); return 0; }
    }

    if (!strcmp(role, "aggregator")) {
        // ready_fd not used in standalone mode
        return aggregator_main(-1, producers);
    } else if (!strcmp(role, "producer")) {
        return producer_main(id, duration, rate, seed);
    }

    // Supervisor role
    if (install_signal_handlers() == -1) { perror("sig"); return 1; }

    // Bootstrap IPC resources
    // Create MQ (if not exists)
    mqd_t mqd = mq_create_or_open(MQ_NAME, sizeof(Event), 32, 1);
    if (mqd == (mqd_t)-1) return 1;
    mq_close_and_optionally_unlink(mqd, MQ_NAME, 0);

    // Create SHM & semaphore
    shm_ctx_t shm; 
    if (shm_open_map_init(SHM_NAME, SEM_NAME, &shm) == -1) {
        fprintf(stderr, "supervisor shm init failed\n");
        return 1;
    }
    shm_close_unmap(&shm, 0);

    // Ensure FIFO exists
    if (fifo_ensure(FIFO_PATH) == -1) {
        perror("mkfifo");
        return 1;
    }

    // Pipe for aggregator readiness
    int pfd[2]; CHECK(pipe(pfd));
    // Disable close-on-exec so exec children won't inherit? Here only aggregator uses it.
    int flags = fcntl(pfd[1], F_GETFD); fcntl(pfd[1], F_SETFD, flags & ~FD_CLOEXEC);

    pid_t agg_pid = fork();
    CHECK(agg_pid);
    if (agg_pid == 0) {
        close(pfd[0]); // child writes READY
        // Start aggregator (no exec)
        exit(aggregator_main(pfd[1], producers));
    }
    close(pfd[1]);

    // Wait for READY
    char buf[16] = {0};
    read(pfd[0], buf, sizeof(buf)-1);
    close(pfd[0]);

    // Fork + exec producers
    pid_t pids[MAX_PRODUCERS];
    int actual = producers;
    if (actual > MAX_PRODUCERS) actual = MAX_PRODUCERS;

    for (int i = 0; i < actual; ++i) {
        pid_t c = fork();
        CHECK(c);
        if (c == 0) {
            char idbuf[16], durbuf[16], ratebuf[16], seedbuf[16];
            snprintf(idbuf, sizeof idbuf, "--id=%d", i);
            snprintf(durbuf, sizeof durbuf, "--duration=%d", duration);
            snprintf(ratebuf, sizeof ratebuf, "--rate=%d", rate);
            snprintf(seedbuf, sizeof seedbuf, "--seed=%u", seed + (unsigned)i);
            execlp(argv[0], argv[0], "--role=producer", idbuf, durbuf, ratebuf, seedbuf, (char*)NULL);
            // If exec fails:
            perror("exec producer");
            _exit(127);
        } else {
            pids[i] = c;
        }
    }

    // Let simulation run for 'duration' seconds, then signal stop
    time_t t0 = time(NULL);
    while (!g_stop && (time(NULL) - t0 < duration + 2)) {
        sleep(1);
    }

    // Graceful shutdown
    kill(agg_pid, SIGTERM);
    for (int i = 0; i < actual; ++i) kill(pids[i], SIGTERM);

    // Reap
    int status;
    waitpid(agg_pid, &status, 0);
    for (int i = 0; i < actual; ++i) waitpid(pids[i], &status, 0);

    // Cleanup IPC (unlink)
    mq_unlink(MQ_NAME);
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);
    unlink(FIFO_PATH);

    return 0;
}