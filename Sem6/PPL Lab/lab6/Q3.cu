#include <stdio.h>
#include <cuda.h>
#include <stdlib.h>

__global__ void evenPhaseKernel(int *arr, int n) {

    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int i = 2 * tid;   // even index

    if (i + 1 < n) {
        if (arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}

__global__ void oddPhaseKernel(int *arr, int n) {

    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int i = 2 * tid + 1;   // odd index

    if (i + 1 < n) {
        if (arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}

int main() {

    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *h_arr = (int*)malloc(n * sizeof(int));

    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &h_arr[i]);

    int *d_arr;
    cudaMalloc(&d_arr, n * sizeof(int));
    cudaMemcpy(d_arr, h_arr, n * sizeof(int), cudaMemcpyHostToDevice);

    // Number of comparison pairs ≈ n/2
    dim3 blockDim(256);
    dim3 gridDim((n/2 + blockDim.x - 1) / blockDim.x);

    // Perform n phases
    for (int i = 0; i < n; i++) {

        if (i % 2 == 0)
            evenPhaseKernel<<<gridDim, blockDim>>>(d_arr, n);
        else
            oddPhaseKernel<<<gridDim, blockDim>>>(d_arr, n);

        cudaDeviceSynchronize();
    }

    cudaMemcpy(h_arr, d_arr, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", h_arr[i]);

    cudaFree(d_arr);
    free(h_arr);

    return 0;
}
