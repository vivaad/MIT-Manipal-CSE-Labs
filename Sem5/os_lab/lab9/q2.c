#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int start;
    int end;
    int result;
} SumData;

void* calculate_sum(void* arg) {
    SumData* data = (SumData*)arg;
    int sum = 0;
    for (int i = data->start; i <= data->end; i++) {
        sum += i;
    }
    data->result = sum;
    pthread_exit(NULL);
}

int main() {
    SumData data;
    data.start = 0;

    printf("Enter the non-negative integer up to which to sum: ");
    scanf("%d", &data.end);
    if (data.end < 0) {
        printf("Please enter a non-negative integer.\n");
        return 1;
    }

    pthread_t tid;
    if (pthread_create(&tid, NULL, calculate_sum, &data) != 0) {
        printf("Error creating thread.\n");
        return 1;
    }

    pthread_join(tid, NULL);

    printf("Summation result: %d\n", data.result);

    return 0;
}

