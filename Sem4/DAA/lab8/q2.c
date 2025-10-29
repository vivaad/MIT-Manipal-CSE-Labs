#include <stdio.h>
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void heapify(int arr[], int N, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < N && arr[left] > arr[largest])

		largest = left;

	if (right < N && arr[right] > arr[largest])

		largest = right;

	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, N, largest);
	}
}
void heapSort(int arr[], int N)
{
	for (int i = N / 2 - 1; i >= 0; i--)
		heapify(arr, N, i);

	for (int i = N - 1; i >= 0; i--) {
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}

void printArray(int arr[], int N)
{
	for (int i = 0; i < N; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

// int main()
// {
// 	/* int arr[] = {2,9,7,6,5,8}; */
// 	int N;
// 	printf("N:");
// 	scanf("%d", &N);
// 	int arr[N];
// 	for(int i=0; i<N; i++)
// 		scanf("%d", &arr[i]);

// 	heapSort(arr, N);
// 	printf("Sorted array is\n");
// 	printArray(arr, N);
// }


#include <time.h>

int main()
{
    int N;
    printf("Enter the size of array: ");
    scanf("%d", &N);

    int arr[N];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    clock_t start, end;
    start = clock();

    heapSort(arr, N);

    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorted array is:\n");
    printArray(arr, N);

    printf("Time taken for heap sort: %f seconds\n", time_taken);
    return 0;
}