#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define FIFO_NAME "/tmp/newFifo"

int main() {
    int pipe_fd;
    int num, output;

    // read from named pipe
    pipe_fd = open(FIFO_NAME, O_RDONLY);

    read(pipe_fd, &num, sizeof(num));
    close(pipe_fd);

    // calculate square number
    output = 2*num;

    // write to named pipe
    pipe_fd = open(FIFO_NAME, O_WRONLY);

    write(pipe_fd, &output, sizeof(output));
    close(pipe_fd);

    return 0;
}
