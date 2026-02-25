#ifndef SIGNALS_H
#define SIGNALS_H
#include <signal.h>

extern volatile sig_atomic_t g_stop;
extern volatile sig_atomic_t g_dump;

int install_signal_handlers(void);

#endif