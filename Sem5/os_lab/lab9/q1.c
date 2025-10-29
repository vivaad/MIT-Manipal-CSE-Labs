#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *fibSequence;  // shared array
int count;         // number of Fibonacci numbers to generate

void* generateFibonacci(void* arg) {
    if (count <= 0) pthread_exit(NULL);

    fibSequence[0] = 0;
    if (count == 1) pthread_exit(NULL);

    fibSequence[1] = 1;

    for (int i = 2; i < count; i++) {
        fibSequence[i] = fibSequence[i-1] + fibSequence[i-2];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_fibonacci_terms>\n", argv[0]);
        return 1;
    }

    count = atoi(argv[1]);
    if (count <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    fibSequence = (int*) malloc(sizeof(int) * count);
    if (fibSequence == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    pthread_t tid;

    // Create child thread
    if (pthread_create(&tid, NULL, generateFibonacci, NULL) != 0) {
        printf("Failed to create thread.\n");
        free(fibSequence);
        return 1;
    }

    // Wait for child thread to finish
    pthread_join(tid, NULL);

    // Parent prints the generated Fibonacci sequence
    printf("Fibonacci sequence (%d terms):\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", fibSequence[i]);
    }
    printf("\n");

    free(fibSequence);
    return 0;
}

