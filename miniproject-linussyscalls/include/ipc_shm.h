#ifndef IPC_SHM_H
#define IPC_SHM_H
#include "common.h"

typedef struct {
    Snapshot *snap;
    int shm_fd;
    sem_t *sem;
    int creator; // 1 if created by this process
} shm_ctx_t;

int  shm_open_map_init(const char *shm_name, const char *sem_name, shm_ctx_t *ctx);
void shm_close_unmap(shm_ctx_t *ctx, int unlink_all);
void shm_lock(shm_ctx_t *ctx);
void shm_unlock(shm_ctx_t *ctx);

#endif