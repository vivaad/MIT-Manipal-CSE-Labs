#include "cuda_runtime.h"	  		
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void vector_additionNblocks(int *a, int *b, int *c, int n){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if(tid < n)
        c[tid] = a[tid] + b[tid];
}

__global__ void vector_additionNthreads(int *a, int *b, int *c, int n){
    int tid = threadIdx.x;
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

    printf("Enter elements of first vector:\n");
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    printf("Enter elements of second vector:\n");
      for(int i = 0; i < n; i++){
        scanf("%d", &b[i]);
    }

    int *d_a, *d_b, *d_c;

    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    vector_additionNblocks<<<n, 1>>>(d_a, d_b, d_c, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    printf("\nResult using N blocks (1 thread per block):\n");
    for(int i = 0; i < n; i++){
        printf("%d ", c[i]);
    }
    printf("\n");

    vector_additionNthreads<<<1, n>>>(d_a, d_b, d_c, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    printf("\nResult using N threads (1 block):\n");
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
