#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_PRODUCERS 8
#define RING_CAPACITY 64

#define MQ_NAME   "/sim_mq1"
#define SHM_NAME  "/sim_shm1"
#define SEM_NAME  "/sim_sem1"
#define FIFO_PATH "/tmp/sim_fifo_ctrl"
#define LOG_PATH  "events.log"
#define SNAPSHOT_PATH "snapshot.txt"

#define CHECK(x) do { if ((x) == -1) { \
  fprintf(stderr, "[%s:%d] %s failed: %s\n", __FILE__, __LINE__, #x, strerror(errno)); \
  exit(EXIT_FAILURE); } } while(0)

typedef struct {
    int producer_id;
    int value;
    int reserved;       // padding
    long ts_sec;
    long ts_nsec;
} Event;

typedef struct {
    int latest_value[MAX_PRODUCERS];
    int total_events;
} Snapshot;

static inline long now_ns(void) {
    struct timespec ts; clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

#endif