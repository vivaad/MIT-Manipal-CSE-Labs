#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, wrt;
int readcount = 0;
int shared_data = 0; // the shared resource

void* reader(void* arg) {
    int id = *((int*)arg);

    // Reader wants to read
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);  // first reader locks writer
    sem_post(&mutex);

    // Reading section
    printf("Reader %d is reading shared_data = %d\n", id, shared_data);

    // Done reading
    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);  // last reader unlocks writer
    sem_post(&mutex);

    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = *((int*)arg);

    sem_wait(&wrt); // lock resource exclusively

    // Writing section
    shared_data += 10;
    printf("Writer %d updated shared_data to %d\n", id, shared_data);

    sem_post(&wrt); // unlock resource

    pthread_exit(NULL);
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_t r[5], w[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&r[i], NULL, reader, &reader_ids[i]);
    }
    // Create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&w[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads
    for (int i = 0; i < 5; i++) pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}

