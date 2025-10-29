#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3
#define CUSTOMERS 10

sem_t waitingRoom;    // number of free seats
sem_t barberChair;    // barber ready to cut hair
sem_t barberSleep;    // barber sleeping/waking up
sem_t seatBelt;       // customer is getting haircut

int done = 0;

void* barber(void* arg) {
    while (!done) {
        // Barber sleeps if no customers
        sem_wait(&barberSleep);
        if (done) break;

        // Barber ready to cut hair
        printf("Barber: Cutting hair...\n");
        sleep(2); // simulate haircut time

        printf("Barber: Done cutting hair.\n");
        sem_post(&seatBelt);  // let customer leave
    }
    printf("Barber: Finished for the day.\n");
    pthread_exit(NULL);
}

void* customer(void* arg) {
    int id = *((int*)arg);

    // Try to enter waiting room
    if (sem_trywait(&waitingRoom) == 0) {
        printf("Customer %d: Sitting in waiting room.\n", id);

        // Wait for barber chair to be free
        sem_wait(&barberChair);

        // Leave waiting room seat
        sem_post(&waitingRoom);

        // Wake up barber if sleeping
        sem_post(&barberSleep);

        // Getting haircut
        printf("Customer %d: Getting haircut.\n", id);
        sem_wait(&seatBelt);

        // Release barber chair after haircut
        sem_post(&barberChair);

        printf("Customer %d: Leaving after haircut.\n", id);
    } else {
        // No chairs available, customer leaves
        printf("Customer %d: No chairs available, leaving.\n", id);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t barberThread;
    pthread_t customers[CUSTOMERS];
    int customer_ids[CUSTOMERS];

    sem_init(&waitingRoom, 0, CHAIRS);
    sem_init(&barberChair, 0, 1);
    sem_init(&barberSleep, 0, 0);
    sem_init(&seatBelt, 0, 0);

    pthread_create(&barberThread, NULL, barber, NULL);

    for (int i = 0; i < CUSTOMERS; i++) {
        customer_ids[i] = i + 1;
        sleep(rand() % 3);  // customers arrive at random intervals
        pthread_create(&customers[i], NULL, customer, &customer_ids[i]);
    }

    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }

    done = 1;
    sem_post(&barberSleep);  // wake up barber to exit
    pthread_join(barberThread, NULL);

    sem_destroy(&waitingRoom);
    sem_destroy(&barberChair);
    sem_destroy(&barberSleep);
    sem_destroy(&seatBelt);

    printf("Barber shop is closed.\n");
    return 0;
}

