// border_replace.cu
#include <stdio.h>
#include <cuda.h>

__global__ void process(int *A, int *B, int rows, int cols) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;

    if (idx < rows * cols) {
        int r = idx / cols;
        int c = idx % cols;

        if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
            B[idx] = A[idx];  // border
        else
            B[idx] = ~A[idx]; // 1's complement
    }
}

int main() {
    int rows = 4, cols = 4;

    int h_A[] = {
        1,2,3,4,
        6,5,8,3,
        2,4,10,1,
        9,1,2,5
    };

    int h_B[16];

    int *d_A, *d_B;

    cudaMalloc(&d_A, 16 * sizeof(int));
    cudaMalloc(&d_B, 16 * sizeof(int));

    cudaMemcpy(d_A, h_A, 16 * sizeof(int), cudaMemcpyHostToDevice);

    process<<<1, 16>>>(d_A, d_B, rows, cols);

    cudaMemcpy(h_B, d_B, 16 * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Output:\n");
    for (int i = 0; i < 16; i++) {
        printf("%d ", h_B[i]);
        if ((i+1)%cols==0) printf("\n");
    }

    return 0;
}