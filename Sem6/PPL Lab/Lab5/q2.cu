#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define THREADS_PER_BLOCK 256

__global__ void vector_addition(int *a, int *b, int *c, int n){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if(tid < n)
        c[tid] = a[tid] + b[tid];
}

int main(){
    int n;

    printf("Enter the value of N: ");
    scanf("%d", &n);

    int size = n * sizeof(int);

    int *a = (int*)malloc(size);
    int *b = (int*)malloc(size);
    int *c = (int*)malloc(size);

    for(int i = 0; i < n; i++){
        a[i] = i;
        b[i] = i + 10;
    }

    int *d_a, *d_b, *d_c;

    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    int blocks = ceil((float)n / THREADS_PER_BLOCK);

    vector_addition<<<blocks, THREADS_PER_BLOCK>>>(d_a, d_b, d_c, n);

    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    printf("\nFirst input array (a):\n");
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("\nSecond input array (b):\n");
    for(int i = 0; i < n; i++){
        printf("%d ", b[i]);
    }
    printf("\n");

    printf("\nResult after vector addition:\n");
    for(int i = 0; i < n; i++){
        printf("%d ", c[i]);
    }
    printf("\n");

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    free(a);
    free(b);
    free(c);

    return 0;
}
