#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H
#include "common.h"

typedef struct {
    Event buf[RING_CAPACITY];
    int head, tail, count;
    pthread_mutex_t m;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} tq_t;

int  tq_init(tq_t *q);
void tq_destroy(tq_t *q);
void tq_push(tq_t *q, const Event *ev);
int  tq_pop(tq_t *q, Event *ev); // returns 0 on success, -1 if stopping

#endif