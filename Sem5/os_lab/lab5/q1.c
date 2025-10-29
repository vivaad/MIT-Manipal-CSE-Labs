#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child: Doing some work...\n");
        sleep(2);  // simulate work by sleeping
        printf("Child: Done.\n");
        return 42; // Child exit code
    }
    else {
        // Parent process
        int status;
        printf("Parent: Waiting for child to finish...\n");

        wait(&status);  // wait for child to terminate

        if (WIFEXITED(status)) {
            printf("Parent: Child exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child terminated abnormally\n");
        }
    }
    return 0;
}

