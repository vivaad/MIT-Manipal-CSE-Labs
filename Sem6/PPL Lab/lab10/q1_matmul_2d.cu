// Q1: Matrix Multiplication using 2D Grid and 2D Block
#include <stdio.h>
#include <cuda.h>

#define N 4  // Matrix size NxN (can be changed)

__global__ void matMul(int *A, int *B, int *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {
        int sum = 0;
        for (int k = 0; k < n; k++) {
            sum += A[row * n + k] * B[k * n + col];
        }
        C[row * n + col] = sum;
    }
}

int main() {
    int n = N;
    int size = n * n * sizeof(int);

    int h_A[N*N], h_B[N*N], h_C[N*N];

    // Initialize matrices
    printf("Matrix A:\n");
    for (int i = 0; i < n * n; i++) {
        h_A[i] = i + 1;
        if ((i + 1) % n == 0) printf("%d\n", h_A[i]);
        else printf("%d ", h_A[i]);
    }

    printf("Matrix B:\n");
    for (int i = 0; i < n * n; i++) {
        h_B[i] = (i % n == i / n) ? 1 : 0;  // Identity matrix
        if ((i + 1) % n == 0) printf("%d\n", h_B[i]);
        else printf("%d ", h_B[i]);
    }

    int *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // 2D Block and 2D Grid
    dim3 blockDim(2, 2);
    dim3 gridDim((n + blockDim.x - 1) / blockDim.x,
                 (n + blockDim.y - 1) / blockDim.y);

    matMul<<<gridDim, blockDim>>>(d_A, d_B, d_C, n);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    printf("Result Matrix C = A x B:\n");
    for (int i = 0; i < n * n; i++) {
        if ((i + 1) % n == 0) printf("%d\n", h_C[i]);
        else printf("%d ", h_C[i]);
    }

    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    return 0;
}
