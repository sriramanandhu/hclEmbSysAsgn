#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY 10
#define MEM_SIZE 1024

int main() {
    int shmid;
    int uid, gid, mode;
    struct shmid_ds shmid_ds, *buf;
    buf = &shmid_ds;

    if ((shmid = shmget(KEY, MEM_SIZE, 0)) == -1) {
        perror("shmid");
        exit(1);
    }

    if (shmctl(shmid, IPC_STAT, buf) == -1) {
        perror("shmctl");
        exit(1);
    }

    printf("\n\tIPC_SET\n");
    printf("Enter User ID = ");
    scanf("%d", &uid);
    buf->shm_perm.uid = uid;
    printf("User ID = %d\n", buf->shm_perm.uid);

    printf("Enter Group ID = ");
    scanf("%d", &gid);
    buf->shm_perm.gid = gid;
    printf("Group ID = %d\n", buf->shm_perm.gid);

    printf("Enter Mode in octal = ");
    scanf("%o", &mode);
    buf->shm_perm.mode = mode;
    printf("Mode = 0%o\n", buf->shm_perm.mode);

    // do the change
    shmctl(shmid, IPC_SET, buf);

    return 0;
}