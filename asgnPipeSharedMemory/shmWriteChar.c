#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#define KEY 10
#define MEM_SIZE 1024

int main() {
    int shmId;
    char *msg;
    if ((shmId = shmget(KEY, MEM_SIZE, IPC_CREAT|0666)) == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    msg = shmat(shmId, (void *)0, 0);
    if (msg == (void *) -1) {
        perror("Shared memory attach");
        fprintf(stderr, "(%d:%s)\n", errno, strerror(errno));
        return 1;
    }

    printf("enter the data to written to shared memory: ");
    fgets(msg, MEM_SIZE, stdin);
    printf("written successfully\n");
    shmdt(msg);

    return 0;
}