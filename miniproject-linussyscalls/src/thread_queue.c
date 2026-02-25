#include "thread_queue.h"

int tq_init(tq_t *q) {
    memset(q, 0, sizeof(*q));
    pthread_mutex_init(&q->m, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
    return 0;
}

void tq_destroy(tq_t *q) {
    pthread_mutex_destroy(&q->m);
    pthread_cond_destroy(&q->not_empty);
    pthread_cond_destroy(&q->not_full);
}

void tq_push(tq_t *q, const Event *ev) {
    pthread_mutex_lock(&q->m);
    while (q->count == RING_CAPACITY && !g_stop) {
        pthread_cond_wait(&q->not_full, &q->m);
    }
    if (g_stop) { pthread_mutex_unlock(&q->m); return; }
    q->buf[q->tail] = *ev;
    q->tail = (q->tail + 1) % RING_CAPACITY;
    q->count++;
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->m);
}

int tq_pop(tq_t *q, Event *ev) {
    pthread_mutex_lock(&q->m);
    while (q->count == 0 && !g_stop) {
        pthread_cond_wait(&q->not_empty, &q->m);
    }
    if (q->count == 0 && g_stop) { pthread_mutex_unlock(&q->m); return -1; }
    *ev = q->buf[q->head];
    q->head = (q->head + 1) % RING_CAPACITY;
    q->count--;
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->m);
    return 0;
}