#ifndef IPC_MQ_H
#define IPC_MQ_H
#include "common.h"

mqd_t mq_create_or_open(const char *name, long msgsize, long maxmsg, int create);
int   mq_send_event(mqd_t mqd, const Event *ev, unsigned prio);
int   mq_recv_event(mqd_t mqd, Event *ev);
int   mq_close_and_optionally_unlink(mqd_t mqd, const char *name, int unlink_flag);

#endif