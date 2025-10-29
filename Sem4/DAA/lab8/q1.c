#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global variables to count operations
int heapify_comparisons = 0;
int heapify_swaps = 0;

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    heapify_swaps++;  // Increment swap count
}

void heapify(int arr[], int N, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // Compare left child with current largest
    heapify_comparisons++;
    if (l < N && arr[l] > arr[largest])
        largest = l;

    // Compare right child with current largest
    heapify_comparisons++;
    if (r < N && arr[r] > arr[largest])
        largest = r;

    // If largest is not i, swap and recursively heapify
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, N, largest);
    }
}

void buildHeap(int arr[], int N)
{
    int startIdx = (N / 2) - 1;
    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, N, i);
    }
}

void printHeap(int arr[], int N)
{
    printf("Array representation of Heap is:\n");
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    // Seed random number generator
    srand(time(NULL));

    // Generate random size for the array
    int N = rand() % 100 + 1;  // Generate random size between 1 and 100

    // Dynamically allocate memory for the array
    int arr[N];

    // Populate the array with random integers
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;  // Generate random integers between 0 and 99
    }

    // Build the heap from the array
    buildHeap(arr, N);

    // Print the resulting heap
    printHeap(arr, N);

    // Print operation counts
    printf("\nOperation Counts:\n");
    printf("Heapify Comparisons: %d\n", heapify_comparisons);
    printf("Heapify Swaps: %d\n", heapify_swaps);

    return 0;
}
