// row_transform.cu
#include <stdio.h>
#include <cuda.h>

__global__ void transform(int *A, int *B, int rows, int cols) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;

    if (idx < rows * cols) {
        int row = idx / cols;
        int val = A[idx];

        if (row == 1)
            B[idx] = val * val;
        else if (row == 2)
            B[idx] = val * val * val;
        else
            B[idx] = val;
    }
}

int main() {
    int rows = 3, cols = 3;

    int h_A[] = {
        1,2,3,
        4,5,6,
        7,8,9
    };

    int h_B[9];

    int *d_A, *d_B;

    cudaMalloc(&d_A, 9 * sizeof(int));
    cudaMalloc(&d_B, 9 * sizeof(int));

    cudaMemcpy(d_A, h_A, 9 * sizeof(int), cudaMemcpyHostToDevice);

    transform<<<1, 9>>>(d_A, d_B, rows, cols);

    cudaMemcpy(h_B, d_B, 9 * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Output:\n");
    for (int i = 0; i < 9; i++) {
        printf("%d ", h_B[i]);
        if ((i+1)%cols==0) printf("\n");
    }

    return 0;
}