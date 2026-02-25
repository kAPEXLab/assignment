#include "ipc_shm.h"

int shm_open_map_init(const char *shm_name, const char *sem_name, shm_ctx_t *ctx) {
    memset(ctx, 0, sizeof(*ctx));
    int created = 0;
    int fd = shm_open(shm_name, O_RDWR | O_CREAT | O_EXCL, 0666);
    if (fd == -1 && errno == EEXIST) {
        fd = shm_open(shm_name, O_RDWR, 0666);
        if (fd == -1) return -1;
        created = 0;
    } else if (fd >= 0) {
        created = 1;
        CHECK(ftruncate(fd, sizeof(Snapshot)));
    } else {
        return -1;
    }

    void *p = mmap(NULL, sizeof(Snapshot), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) { close(fd); return -1; }

    ctx->shm_fd = fd;
    ctx->snap = (Snapshot*)p;
    ctx->creator = created;

    sem_t *sem = sem_open(sem_name, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) { munmap(p, sizeof(Snapshot)); close(fd); return -1; }
    ctx->sem = sem;

    if (created) {
        // Initialize shared snapshot
        memset(ctx->snap, 0, sizeof(Snapshot));
    }
    return 0;
}

void shm_close_unmap(shm_ctx_t *ctx, int unlink_all) {
    if (!ctx) return;
    if (ctx->snap) munmap(ctx->snap, sizeof(Snapshot));
    if (ctx->shm_fd >= 0) close(ctx->shm_fd);
    if (ctx->sem) sem_close(ctx->sem);

    if (unlink_all) {
        shm_unlink(SHM_NAME);
        sem_unlink(SEM_NAME);
    }
}

void shm_lock(shm_ctx_t *ctx) { sem_wait(ctx->sem); }
void shm_unlock(shm_ctx_t *ctx) { sem_post(ctx->sem); }