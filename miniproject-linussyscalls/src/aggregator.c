#include "roles.h"
#include "ipc_mq.h"
#include "ipc_shm.h"
#include "ipc_fifo.h"
#include "logio.h"
#include "thread_queue.h"
#include "signals.h"

typedef struct {
    mqd_t mqd;
    shm_ctx_t shm;
    int fifo_rd;
    log_ctx_t logc;
    tq_t q;
    int producer_count;
} agg_ctx_t;

static void *rx_thread_fn(void *arg) {
    agg_ctx_t *ctx = (agg_ctx_t*)arg;
    while (!g_stop) {
        Event ev;
        if (mq_recv_event(ctx->mqd, &ev) == -1) {
            if (errno == EINTR) continue; // interrupted by signal
            usleep(1000);
            continue;
        }
        tq_push(&ctx->q, &ev);
    }
    return NULL;
}

static void write_snapshot_to_file(agg_ctx_t *ctx) {
    int fd = open(SNAPSHOT_PATH, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (fd == -1) return;
    char line[128];
    shm_lock(&ctx->shm);
    int n = snprintf(line, sizeof(line), "total_events=%d\n", ctx->shm.snap->total_events);
    write(fd, line, n);
    for (int i = 0; i < ctx->producer_count && i < MAX_PRODUCERS; ++i) {
        n = snprintf(line, sizeof(line), "producer[%d]=%d\n", i, ctx->shm.snap->latest_value[i]);
        write(fd, line, n);
    }
    shm_unlock(&ctx->shm);
    close(fd);
}

static void handle_fifo_commands(agg_ctx_t *ctx) {
    char buf[128];
    ssize_t n = fifo_read_cmd(ctx->fifo_rd, buf, sizeof(buf)-1);
    if (n > 0) {
        buf[n] = '\0';
        if (strstr(buf, "DUMP")) {
            write_snapshot_to_file(ctx);
        }
    }
}

static void *persist_thread_fn(void *arg) {
    agg_ctx_t *ctx = (agg_ctx_t*)arg;
    Event ev;
    while (!g_stop) {
        if (tq_pop(&ctx->q, &ev) == -1) break;

        // Update shared memory snapshot
        shm_lock(&ctx->shm);
        if (ev.producer_id >= 0 && ev.producer_id < MAX_PRODUCERS) {
            ctx->shm.snap->latest_value[ev.producer_id] = ev.value;
        }
        ctx->shm.snap->total_events += 1;
        shm_unlock(&ctx->shm);

        // Log event
        log_write_event(&ctx->logc, &ev);

        // Handle FIFO command opportunistically
        handle_fifo_commands(ctx);

        if (g_dump) {
            write_snapshot_to_file(ctx);
            g_dump = 0;
        }
    }
    return NULL;
}

int aggregator_main(int ready_fd, int producer_count) {
    if (install_signal_handlers() == -1) { perror("sig"); return 1; }

    // Signal READY to parent via pipe (if provided)
    if (ready_fd >= 0) {
        const char *msg = "READY\n";
        write(ready_fd, msg, strlen(msg));
        close(ready_fd);
    }

    agg_ctx_t ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.producer_count = producer_count;

    // Open existing MQ (created by supervisor)
    ctx.mqd = mq_create_or_open(MQ_NAME, sizeof(Event), 32, 0);
    if (ctx.mqd == (mqd_t)-1) return 1;

    // Open/Map shared memory
    if (shm_open_map_init(SHM_NAME, SEM_NAME, &ctx.shm) == -1) {
        fprintf(stderr, "shm init failed\n");
        return 1;
    }

    // FIFO read end
    fifo_ensure(FIFO_PATH);
    ctx.fifo_rd = fifo_open_rd_nonblock(FIFO_PATH);

    // Log file
    if (log_open_with_header(&ctx.logc, LOG_PATH) == -1) {
        perror("log_open");
        return 1;
    }

    // Internal queue + threads
    tq_init(&ctx.q);

    pthread_t t_rx, t_persist;
    pthread_create(&t_rx, NULL, rx_thread_fn, &ctx);
    pthread_create(&t_persist, NULL, persist_thread_fn, &ctx);

    // Wait for stop
    while (!g_stop) {
        sleep(1);
    }

    // Join and cleanup
    pthread_mutex_lock(&ctx.q.m);
    g_stop = 1;
    pthread_cond_broadcast(&ctx.q.not_empty);
    pthread_cond_broadcast(&ctx.q.not_full);
    pthread_mutex_unlock(&ctx.q.m);

    pthread_join(t_rx, NULL);
    pthread_join(t_persist, NULL);

    tq_destroy(&ctx.q);
    log_finalize(&ctx.logc);
    log_close(&ctx.logc);
    if (ctx.fifo_rd >= 0) close(ctx.fifo_rd);
    mq_close_and_optionally_unlink(ctx.mqd, MQ_NAME, 0);
    shm_close_unmap(&ctx.shm, 0);
    return 0;
}