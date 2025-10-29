#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int* array;
    int size;
    int sum;
} SumArray;

void* sum_even(void* arg) {
    SumArray* data = (SumArray*)arg;
    int sum = 0;
    for (int i = 0; i < data->size; i++) {
        if (data->array[i] % 2 == 0)
            sum += data->array[i];
    }
    data->sum = sum;
    pthread_exit(NULL);
}

void* sum_odd(void* arg) {
    SumArray* data = (SumArray*)arg;
    int sum = 0;
    for (int i = 0; i < data->size; i++) {
        if (data->array[i] % 2 != 0)
            sum += data->array[i];
    }
    data->sum = sum;
    pthread_exit(NULL);
}

int main() {
    int n;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    SumArray evenData = {arr, n, 0};
    SumArray oddData = {arr, n, 0};

    pthread_t tid_even, tid_odd;

    if (pthread_create(&tid_even, NULL, sum_even, &evenData) != 0) {
        printf("Error creating even sum thread.\n");
        free(arr);
        return 1;
    }

    if (pthread_create(&tid_odd, NULL, sum_odd, &oddData) != 0) {
        printf("Error creating odd sum thread.\n");
        free(arr);
        return 1;
    }

    pthread_join(tid_even, NULL);
    pthread_join(tid_odd, NULL);

    printf("Sum of even numbers: %d\n", evenData.sum);
    printf("Sum of odd numbers: %d\n", oddData.sum);

    free(arr);
    return 0;
}

