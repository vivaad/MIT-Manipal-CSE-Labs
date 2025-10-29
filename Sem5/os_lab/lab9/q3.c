#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
} PrimeData;

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void* generate_primes(void* arg) {
    PrimeData* data = (PrimeData*)arg;
    printf("Prime numbers between %d and %d are:\n", data->start, data->end);
    for (int i = data->start; i <= data->end; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    pthread_exit(NULL);
}

int main() {
    PrimeData data;

    printf("Enter the starting number: ");
    scanf("%d", &data.start);

    printf("Enter the ending number: ");
    scanf("%d", &data.end);

    if (data.start > data.end) {
        printf("Invalid input: start should be <= end.\n");
        return 1;
    }

    pthread_t tid;
    if (pthread_create(&tid, NULL, generate_primes, &data) != 0) {
        printf("Error creating thread.\n");
        return 1;
    }

    pthread_join(tid, NULL);

    return 0;
}

