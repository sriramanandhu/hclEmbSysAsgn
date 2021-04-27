#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define FIFO_NAME "/tmp/newFifo"

int main() {
    int num, output, res;
    // make fifo named pipe
    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    printf("Enter a num ");
    scanf("%d", &num);
    pid_t p = fork();

    if (p < 0) {
        perror("fork");
        return 1;
    }

    // parent process
    else if (p > 0) {
        // write to pipe
        int pipe_fd = open(FIFO_NAME, O_WRONLY);
        
        res = write(pipe_fd, &num, sizeof(num));
        printf("number %d written to the pipe\n", num);
        close(pipe_fd);
        

        // read from pipe
        pipe_fd = open(FIFO_NAME, O_RDONLY);

        res = read(pipe_fd, &output, sizeof(output));
        printf("number %d read from the pipe\n", output);
        printf("twice of %d is %d\n", num, output);
        close(pipe_fd);

        // Wait for the child process
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    // child process
    else {
        execl("./execlFifoChildProcess", "./execlFifoChildProcess", NULL);
        printf("ending-----");
    }

    return 0;
}
