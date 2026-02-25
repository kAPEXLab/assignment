#include "ipc_fifo.h"

int fifo_ensure(const char *path) {
    if (mkfifo(path, 0666) == -1) {
        if (errno != EEXIST) return -1;
    }
    return 0;
}

int fifo_open_rd_nonblock(const char *path) {
    return open(path, O_RDONLY | O_NONBLOCK);
}

int fifo_open_wr(const char *path) {
    return open(path, O_WRONLY);
}

ssize_t fifo_read_cmd(int fd, char *buf, size_t len) {
    return read(fd, buf, len);
}

int fifo_write_cmd(int fd, const char *cmd) {
    size_t n = strlen(cmd);
    return (int)write(fd, cmd, n);
}