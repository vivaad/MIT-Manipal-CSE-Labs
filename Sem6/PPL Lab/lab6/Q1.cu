#include <stdio.h>
#include <cuda.h>

__global__ void convolution1D(float *N, float *M, float *P,
                              int width, int mask_width) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int half = mask_width / 2;

    if (i < width) {
        float sum = 0.0f;

        for (int j = 0; j < mask_width; j++) {
            int idx = i - half + j;
            if (idx >= 0 && idx < width)
                sum += N[idx] * M[j];
        }
        P[i] = sum;
    }
}

int main() {

    int width, mask_width;

    printf("Enter size of input array: ");
    scanf("%d", &width);

    printf("Enter size of mask: ");
    scanf("%d", &mask_width);

    float *h_N = (float*)malloc(width * sizeof(float));
    float *h_M = (float*)malloc(mask_width * sizeof(float));
    float *h_P = (float*)malloc(width * sizeof(float));

    printf("Enter input array elements:\n");
    for (int i = 0; i < width; i++)
        scanf("%f", &h_N[i]);

    printf("Enter mask elements:\n");
    for (int i = 0; i < mask_width; i++)
        scanf("%f", &h_M[i]);

    float *d_N, *d_M, *d_P;

    cudaMalloc(&d_N, width * sizeof(float));
    cudaMalloc(&d_M, mask_width * sizeof(float));
    cudaMalloc(&d_P, width * sizeof(float));

    cudaMemcpy(d_N, h_N, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, h_M, mask_width * sizeof(float), cudaMemcpyHostToDevice);

    dim3 blockDim(256);
    dim3 gridDim((width + blockDim.x - 1) / blockDim.x);

    convolution1D<<<gridDim, blockDim>>>(d_N, d_M, d_P, width, mask_width);

    cudaMemcpy(h_P, d_P, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Resultant array:\n");
    for (int i = 0; i < width; i++)
        printf("%f ", h_P[i]);

    cudaFree(d_N); cudaFree(d_M); cudaFree(d_P);
    free(h_N); free(h_M); free(h_P);

    return 0;
}
