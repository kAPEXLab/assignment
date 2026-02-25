#include "logio.h"

int log_open_with_header(log_ctx_t *lc, const char *path) {
    lc->fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (lc->fd == -1) return -1;
    lc->count = 0;
    const char *hdr = "COUNT:00000000\n"; // 6 + 8 + 1 = 15 + '\n'
    if (write(lc->fd, hdr, strlen(hdr)) == -1) return -1;
    return 0;
}

int log_write_event(log_ctx_t *lc, const Event *ev) {
    char line[128];
    int n = snprintf(line, sizeof(line), "pid=%d val=%d ts=%ld.%09ld\n",
                     ev->producer_id, ev->value, ev->ts_sec, ev->ts_nsec);
    if (write(lc->fd, line, (size_t)n) == -1) return -1;
    lc->count++;
    return 0;
}

int log_finalize(log_ctx_t *lc) {
    // Seek to after "COUNT:"
    if (lseek(lc->fd, 6, SEEK_SET) == -1) return -1;
    char buf[16];
    // Fixed width 8 digits (truncate if large)
    int n = snprintf(buf, sizeof(buf), "%08d", lc->count);
    if (write(lc->fd, buf, 8) == -1) return -1;
    // Seek to end to be nice
    if (lseek(lc->fd, 0, SEEK_END) == -1) return -1;
    return 0;
}

void log_close(log_ctx_t *lc) {
    if (lc->fd != -1) close(lc->fd);
    lc->fd = -1;
}