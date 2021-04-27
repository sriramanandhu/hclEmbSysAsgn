
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    // two pipes to send and receive data
    int parentToChildFd[2];
    int childToParentFd[2];
    int input_data;
    pid_t p;

    if ((pipe(parentToChildFd) == -1) || (pipe(childToParentFd) == -1)) {
        fprintf(stderr, "Pipe Failed");
        perror("pipe");
        return 1;
    }
    
    printf("Enter a number: ");
    scanf("%d", &input_data);
    p = fork();

    if (p < 0) {
        fprintf(stderr, "fork failed");
        perror("fork");
        return 1;
    }

    // parent process
    else if (p > 0) {
        int output_data;
        close(parentToChildFd[0]); // close reading end of parentToChildFd

        // write data and closing writing end
        write(parentToChildFd[1], &input_data, sizeof(int));
        close(parentToChildFd[1]);

        // Wait for the child process
        wait(NULL);
        close(childToParentFd[1]); // close writing end of childToParentFd

        // read data from child
        read(childToParentFd[0], &output_data, sizeof(int));
        printf("output from child = %d\n", output_data);
        close(childToParentFd[0]);
    }

    // child process
    else {
        close(parentToChildFd[1]); // close writing end of parentToChildFd

        // read data from parent
        int temp_input, output_data;
        read(parentToChildFd[0], &temp_input, sizeof(int));

        // calculate the square of the given number
        output_data = input_data*input_data;
        // close both reading ends
        close(parentToChildFd[0]);
        close(childToParentFd[0]);
        
        // write output to pipe
        write(childToParentFd[1], &output_data, sizeof(int));
        close(childToParentFd[1]);

        exit(0);
    }

    return 0;
}
