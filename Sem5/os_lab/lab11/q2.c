#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define P 3   // number of processes (threads)
#define R 3   // number of resource types

int available[R] = {3, 3, 2};                  // total available resources
int max[P][R] = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2} };  // max demand
int allocation[P][R] = {0};                    // resources currently allocated
int need[P][R];                                // remaining need

pthread_mutex_t lock;

int isSafe() {
    int work[R], finish[P] = {0};
    for (int i = 0; i < R; i++) work[i] = available[i];

    int count = 0;
    while (count < P) {
        int found = 0;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int i;
                for (i = 0; i < R; i++)
                    if (need[p][i] > work[i]) break;

                if (i == R) {
                    for (int j = 0; j < R; j++) work[j] += allocation[p][j];
                    finish[p] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) return 0; // unsafe
    }
    return 1; // safe
}

int request_resources(int pid, int req[]) {
    pthread_mutex_lock(&lock);

    // Check if request is valid
    for (int i = 0; i < R; i++) {
        if (req[i] > need[pid][i] || req[i] > available[i]) {
            pthread_mutex_unlock(&lock);
            return 0;
        }
    }

    // Tentatively allocate
    for (int i = 0; i < R; i++) {
        available[i] -= req[i];
        allocation[pid][i] += req[i];
        need[pid][i] -= req[i];
    }

    int safe = isSafe();
    if (!safe) { // rollback
        for (int i = 0; i < R; i++) {
            available[i] += req[i];
            allocation[pid][i] -= req[i];
            need[pid][i] += req[i];
        }
    }

    pthread_mutex_unlock(&lock);
    return safe;
}

void release_resources(int pid) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < R; i++) {
        available[i] += allocation[pid][i];
        need[pid][i] = max[pid][i];
        allocation[pid][i] = 0;
    }
    pthread_mutex_unlock(&lock);
}

void *process(void *arg) {
    int pid = *(int *)arg;
    int req[R];

    for (int i = 0; i < R; i++) need[pid][i] = max[pid][i];

    for (int step = 0; step < 3; step++) {
        for (int i = 0; i < R; i++)
            req[i] = rand() % (need[pid][i] + 1);

        if (request_resources(pid, req))
            printf("Process %d: Request granted [", pid);
        else
            printf("Process %d: Request denied [", pid);

        for (int i = 0; i < R; i++) printf("%d ", req[i]);
        printf("]\n");

        sleep(1);
    }

    release_resources(pid);
    printf("Process %d: Released resources\n", pid);
    return NULL;
}

int main() {
    pthread_t tid[P];
    int pid[P];

    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < P; i++) pid[i] = i;

    for (int i = 0; i < P; i++)
        pthread_create(&tid[i], NULL, process, &pid[i]);

    for (int i = 0; i < P; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&lock);
    printf("\nAll processes completed.\n");
    return 0;
}

