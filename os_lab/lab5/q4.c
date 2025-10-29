#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child exits immediately
        exit(0);
    }
    else {
        // Parent sleeps without waiting for child (no wait())
        printf("Parent PID=%d, child PID=%d\n", getpid(), pid);
        printf("Parent sleeping... (CTRL+C to terminate)\n");
        sleep(30);  // sleep long enough to check zombie with `ps`
        // Parent exits here, init will adopt zombie if still exists
    }
    return 0;
}

