#include <stdio.h>
#include <stdlib.h>
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
        if (shm->flag == 1) {
            printf("Display: %s\n", shm->msg);
            shm->msg[0] = 0;
            shm->flag = 0;
        } else {
            usleep(100000);
        }
    }

    shmdt(shm);
    return 0;
}

