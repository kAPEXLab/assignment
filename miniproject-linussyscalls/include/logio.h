#ifndef LOGIO_H
#define LOGIO_H
#include "common.h"

typedef struct {
    int fd;
    int count;
} log_ctx_t;

int  log_open_with_header(log_ctx_t *lc, const char *path);
int  log_write_event(log_ctx_t *lc, const Event *ev);
int  log_finalize(log_ctx_t *lc);  // does lseek to update COUNT
void log_close(log_ctx_t *lc);

#endif