#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#define PI 3.1415

const int n = 6;

__global__ void angles_to_sine(double *a, double *b){
    int tid = threadIdx.x;
    if(tid < n) {
        b[tid] = sinf(a[tid]);
    }
}

int main(){
    double *d_a, *d_b; 
    int size = sizeof(double);
    
    cudaMalloc((void**)&d_a, n * size);
    cudaMalloc((void**)&d_b, n * size);

    double a[n] = {0, PI/6, PI/4, PI/3, PI/2, PI};
    double b[n];

    cudaMemcpy(d_a, a, n * size, cudaMemcpyHostToDevice);

    angles_to_sine<<<1,n>>>(d_a, d_b);

    cudaMemcpy(b, d_b, n * size, cudaMemcpyDeviceToHost);

    printf("The 1D array containing sine of angles is: \n");
    for(int i = 0; i < n; i++){
        printf("sin(%.2lf) = %.2lf \n",a[i],b[i]);
    }
    printf("\n");

    cudaFree(d_a);
    cudaFree(d_b);
    return 0;
}
