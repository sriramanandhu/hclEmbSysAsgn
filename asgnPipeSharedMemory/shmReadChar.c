#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY 10
#define MEM_SIZE 1024

int main() {
    int shmId;
    char *msg;
    if ((shmId = shmget(KEY, MEM_SIZE, 0)) == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    perror("shmget");
    msg = shmat(shmId, (void *)0, 0);
    perror("shmat");
    printf("data read from the shared memory is: %s\n", msg);

    shmdt(msg);

    // shmctl(shmId, IPC_RMID, NULL);

    return 0;
}