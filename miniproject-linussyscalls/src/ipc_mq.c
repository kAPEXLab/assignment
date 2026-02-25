#include "ipc_mq.h"

mqd_t mq_create_or_open(const char *name, long msgsize, long maxmsg, int create) {
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = maxmsg;
    attr.mq_msgsize = msgsize;
    attr.mq_curmsgs = 0;

    int flags = O_RDWR;
    if (create) flags |= O_CREAT;

    mqd_t mqd = mq_open(name, flags, 0666, create ? &attr : NULL);
    if (mqd == (mqd_t)-1) {
        fprintf(stderr, "mq_open(%s) failed: %s\n", name, strerror(errno));
    }
    return mqd;
}

int mq_send_event(mqd_t mqd, const Event *ev, unsigned prio) {
    return mq_send(mqd, (const char*)ev, sizeof(Event), prio);
}

int mq_recv_event(mqd_t mqd, Event *ev) {
    ssize_t n = mq_receive(mqd, (char*)ev, sizeof(Event), NULL);
    if (n == -1) return -1;
    return 0;
}

int mq_close_and_optionally_unlink(mqd_t mqd, const char *name, int unlink_flag) {
    int rc = mq_close(mqd);
    if (unlink_flag) mq_unlink(name);
    return rc;
}