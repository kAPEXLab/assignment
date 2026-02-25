#ifndef IPC_FIFO_H
#define IPC_FIFO_H
#include "common.h"

int fifo_ensure(const char *path);
int fifo_open_rd_nonblock(const char *path);
int fifo_open_wr(const char *path);
ssize_t fifo_read_cmd(int fd, char *buf, size_t len);
int fifo_write_cmd(int fd, const char *cmd);

#endif