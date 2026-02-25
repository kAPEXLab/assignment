#include "roles.h"
#include "ipc_mq.h"
#include "signals.h"

int producer_main(int id, int duration_sec, int rate_hz, unsigned seed) {
    if (install_signal_handlers() == -1) { perror("sig"); return 1; }

    mqd_t mqd = mq_create_or_open(MQ_NAME, sizeof(Event), 32, 0);
    if (mqd == (mqd_t)-1) return 1;

    srand(seed + (unsigned)id);
    const int interval_us = rate_hz > 0 ? (1000000 / rate_hz) : 100000;

    time_t start = time(NULL);
    while (!g_stop && (time(NULL) - start < duration_sec)) {
        Event ev;
        ev.producer_id = id;
        ev.value = rand() % 1000;
        struct timespec ts; clock_gettime(CLOCK_REALTIME, &ts);
        ev.ts_sec = ts.tv_sec;
        ev.ts_nsec = ts.tv_nsec;

        if (mq_send_event(mqd, &ev, 1) == -1) {
            if (errno == EINTR) continue;
            usleep(2000);
        }

        usleep(interval_us);
    }

    mq_close_and_optionally_unlink(mqd, MQ_NAME, 0);
    return 0;
}