// Q3: Tiled 1D Convolution using Shared Memory
#include <stdio.h>
#include <cuda.h>

#define MASK_SIZE 5
#define TILE_SIZE 8
#define WIDTH 16

__constant__ int d_M[MASK_SIZE];

__global__ void tiledConvolution1D(int *N, int *P, int width, int maskSize) {
    int halfMask = maskSize / 2;
    int tx = threadIdx.x;
    int i  = blockIdx.x * TILE_SIZE + tx;

    // Shared memory: tile + halo on both sides
    __shared__ int N_s[TILE_SIZE + MASK_SIZE - 1];

    // Load left halo
    int haloLeft = i - halfMask;
    if (tx < halfMask) {
        N_s[tx] = (haloLeft >= 0) ? N[haloLeft] : 0;
    }

    // Load tile data
    if (i < width)
        N_s[tx + halfMask] = N[i];
    else
        N_s[tx + halfMask] = 0;

    // Load right halo
    if (tx >= TILE_SIZE - halfMask) {
        int haloRight = i + halfMask;
        N_s[tx + 2 * halfMask] = (haloRight < width) ? N[haloRight] : 0;
    }

    __syncthreads();

    // Compute convolution from shared memory
    if (i < width) {
        int sum = 0;
        for (int j = 0; j < maskSize; j++) {
            sum += N_s[tx + j] * d_M[j];
        }
        P[i] = sum;
    }
}

int main() {
    int width    = WIDTH;
    int maskSize = MASK_SIZE;

    int h_N[WIDTH]     = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int h_M[MASK_SIZE] = {1, 2, 3, 2, 1};
    int h_P[WIDTH];

    printf("Input Array N (size %d):\n", width);
    for (int i = 0; i < width; i++) printf("%d ", h_N[i]);
    printf("\n");

    printf("Mask M (size %d): ", maskSize);
    for (int i = 0; i < maskSize; i++) printf("%d ", h_M[i]);
    printf("\n");

    // Copy mask to constant memory
    cudaMemcpyToSymbol(d_M, h_M, maskSize * sizeof(int));

    int *d_N, *d_P;
    cudaMalloc(&d_N, width * sizeof(int));
    cudaMalloc(&d_P, width * sizeof(int));

    cudaMemcpy(d_N, h_N, width * sizeof(int), cudaMemcpyHostToDevice);

    int gridSize = (width + TILE_SIZE - 1) / TILE_SIZE;

    tiledConvolution1D<<<gridSize, TILE_SIZE>>>(d_N, d_P, width, maskSize);

    cudaMemcpy(h_P, d_P, width * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Output Array P:\n");
    for (int i = 0; i < width; i++) printf("%d ", h_P[i]);
    printf("\n");

    cudaFree(d_N); cudaFree(d_P);
    return 0;
}
