#include "signals.h"
#include <string.h>

volatile sig_atomic_t g_stop = 0;
volatile sig_atomic_t g_dump = 0;

static void on_signal(int sig) {
    if (sig == SIGINT || sig == SIGTERM) g_stop = 1;
    if (sig == SIGUSR1) g_dump = 1;
}

int install_signal_handlers(void) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = on_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa, NULL) == -1) return -1;
    if (sigaction(SIGTERM, &sa, NULL) == -1) return -1;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) return -1;
    return 0;
}