#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <ctype.h>

int main() {
    int shmid = shmget(5678, 2, 0666 | IPC_CREAT);
    char *shm = (char *)shmat(shmid, NULL, 0);
    pid_t pid = fork();

    if (pid == 0) {
        while (!shm[0]) usleep(1000);
        char c = shm[0];
        shm[0] = 0;
        if (isalpha(c)) c = (c == 'z' || c == 'Z') ? c - 25 : c + 1;
        shm[1] = c;
        shmdt(shm);
        exit(0);
    } else {
        printf("Enter alphabet: ");
        shm[0] = getchar();
        shm[1] = 0;
        while (!shm[1]) usleep(1000);
        printf("Child responded: %c\n", shm[1]);
        wait(NULL);
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}

