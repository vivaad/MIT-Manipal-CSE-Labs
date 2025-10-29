#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define KEY 9999
#define SIZE 256

struct shm {
    int flag;
    char msg[SIZE];
};

int main() {
    int shmid = shmget(KEY, sizeof(struct shm), 0666 | IPC_CREAT);
    struct shm *shm = shmat(shmid, NULL, 0);

    while (1) {
        if (shm->flag == 0) {
            printf("Enter your message: ");
            fgets(shm->msg, SIZE, stdin);
            shm->msg[strcspn(shm->msg, "\n")] = 0;
            shm->flag = 1;
        } else {
            usleep(100000);
        }
    }

    shmdt(shm);
    return 0;
}

