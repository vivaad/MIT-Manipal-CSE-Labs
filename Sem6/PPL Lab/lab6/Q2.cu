#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void selsort(int *a, int *b, int n){
    int tid = blockIdx.x*blockDim.x + threadIdx.x;
    int pos = 0;
    int data = a[tid];
    for(int i=0; i<n; i++){
      if(i == tid)continue;
      if(a[i] < data || (a[i]==data && i<tid))pos++;
    }
    b[pos]=data;
}

int main(void) {
    int n;
    int *h_a, *h_b, *d_a, *d_b; 
    
    printf("Enter size of array");
    scanf("%d", &n);

    int size = n * sizeof(int);

    h_a = (int*)malloc(size);
    h_b = (int*)malloc(size);

    printf("Enter array elements:\n");
    for(int i = 0; i < n; i++)
      scanf("%d", &h_a[i]);;

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);

    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);

    dim3 dimGrid(ceil(n/256.0), 1, 1);
    dim3 dimBlock(256, 1, 1);
    selsort <<< dimGrid, dimBlock >>> (d_a, d_b, n);
    cudaMemcpy(h_b, d_b, size, cudaMemcpyDeviceToHost);
    printf("Resultant sorted array is:\n");
    for(int i = 0; i < n; i++)
      printf("%d ", h_b[i]);
    printf("\n");

    cudaFree(d_a); cudaFree(d_b);
    free(h_a); free(h_b);
    return 0;
}