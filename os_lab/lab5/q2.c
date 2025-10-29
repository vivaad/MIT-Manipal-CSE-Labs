#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    if (fork() == 0) {
        execl("./a.out", NULL);
        perror("execl failed");
        return 1;
    }
    int status;
    wait(&status);
    return 0;
}

