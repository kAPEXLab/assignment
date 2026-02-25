#ifndef ROLES_H
#define ROLES_H
#include "common.h"

int aggregator_main(int ready_fd, int producer_count);
int producer_main(int id, int duration_sec, int rate_hz, unsigned seed);

#endif