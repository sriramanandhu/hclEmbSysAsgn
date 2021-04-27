#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY 10
#define MEM_SIZE 1024

int main() {
    int shmid, rtrn;
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

    printf("\n\tIPC_STAT\n");
    printf("USER ID = %d\n", buf->shm_perm.uid);
    printf("GROUP ID = %d\n", buf->shm_perm.gid);
    printf("creator's ID = %d\n", buf->shm_perm.cuid);
    printf("creator's group ID = %d\n", buf->shm_perm.cgid);
    printf("operation permissions = 0%o\n", buf->shm_perm.mode);
    printf("slot usage sequence number = 0%x\n", buf->shm_perm.__seq);
    printf ("The key= 0%x\n",buf->shm_perm.__key);
    printf ("The segment size = %d\n",buf->shm_segsz);
    printf ("The pid of last shmop = %d\n",buf->shm_lpid);
    printf ("The pid of creator = %d\n",buf->shm_cpid);
    printf ("The current # attached = %d\n",buf->shm_nattch);
    printf("The last shmat time = %ld\n",buf->shm_atime);
    printf("The last shmdt time = %ld\n",buf->shm_dtime);
    printf("The last change time = %ld\n",buf->shm_ctime);

    return 0;
}