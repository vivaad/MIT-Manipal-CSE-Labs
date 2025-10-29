#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 15

int buf[SIZE], f = -1, r = -1;
int produced_count = 0, consumed_count = 0;

sem_t mutex, full, empty;

void *produce(void *arg) {
    for (int i = 0; i < 20; i++) {
        while (1) {
            sem_wait(&mutex);
            if (produced_count - consumed_count < 10) {
                sem_post(&mutex);
                break;
            }
            sem_post(&mutex);
            usleep(100000);
        }

        sem_wait(&empty);
        sem_wait(&mutex);

        buf[(++r) % SIZE] = i;
        produced_count++;
        printf("Produced: %d (P=%d, C=%d)\n", i, produced_count, consumed_count);

        sem_post(&mutex);
        sem_post(&full);

        usleep(90000);
    }
    return NULL;
}

void *consume(void *arg) {
    for (int i = 0; i < 20; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buf[(++f) % SIZE];
        consumed_count++;
        printf("Consumed: %d (P=%d, C=%d)\n", item, produced_count, consumed_count);

        sem_post(&mutex);
        sem_post(&empty);

        usleep(1000000);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, SIZE);

    pthread_create(&p, NULL, produce, NULL);
    pthread_create(&c, NULL, consume, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}

