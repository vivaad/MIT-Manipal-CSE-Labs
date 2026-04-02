// Q2: 1D Parallel Convolution using Constant Memory
#include <stdio.h>
#include <cuda.h>

#define MASK_SIZE 5
#define ARRAY_SIZE 10

// Mask stored in constant memory for fast read-only broadcast
__constant__ int d_M[MASK_SIZE];

__global__ void convolution1D(int *N, int *P, int width, int maskSize) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int halfMask = maskSize / 2;

    if (i < width) {
        int sum = 0;
        for (int j = 0; j < maskSize; j++) {
            int idx = i - halfMask + j;
            if (idx >= 0 && idx < width) {
                sum += N[idx] * d_M[j];
            }
        }
        P[i] = sum;
    }
}

int main() {
    int width = ARRAY_SIZE;
    int maskSize = MASK_SIZE;

    int h_N[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int h_M[MASK_SIZE]  = {1, 2, 3, 2, 1};
    int h_P[ARRAY_SIZE];

    printf("Input Array N: ");
    for (int i = 0; i < width; i++) printf("%d ", h_N[i]);
    printf("\n");

    printf("Mask M: ");
    for (int i = 0; i < maskSize; i++) printf("%d ", h_M[i]);
    printf("\n");

    // Copy mask to constant memory
    cudaMemcpyToSymbol(d_M, h_M, maskSize * sizeof(int));

    int *d_N, *d_P;
    cudaMalloc(&d_N, width * sizeof(int));
    cudaMalloc(&d_P, width * sizeof(int));

    cudaMemcpy(d_N, h_N, width * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 4;
    int gridSize = (width + blockSize - 1) / blockSize;

    convolution1D<<<gridSize, blockSize>>>(d_N, d_P, width, maskSize);

    cudaMemcpy(h_P, d_P, width * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Output Array P: ");
    for (int i = 0; i < width; i++) printf("%d ", h_P[i]);
    printf("\n");

    cudaFree(d_N); cudaFree(d_P);
    return 0;
}
