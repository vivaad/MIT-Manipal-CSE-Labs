// string_RS
#include <stdio.h>
#include <string.h>

__global__ void generateRS(char *S, char *RS, int N) {
    int idx = threadIdx.x;

    if (idx < N) {
        int start = idx * N - (idx * (idx - 1)) / 2; 
        for (int i = 0; i < N - idx; i++) {
            RS[start + i] = S[i];
        }
    }
}

int main() {
    char S[100];
    char *d_S, *d_RS;

    printf("Enter string S: ");
    scanf("%s", S);

    int N = strlen(S);
    int RS_len = N * (N + 1) / 2;

    char *RS = (char*)malloc(RS_len + 1);

    cudaMalloc(&d_S, N);
    cudaMalloc(&d_RS, RS_len);

    cudaMemcpy(d_S, S, N, cudaMemcpyHostToDevice);

    generateRS<<<1, N>>>(d_S, d_RS, N);

    cudaMemcpy(RS, d_RS, RS_len, cudaMemcpyDeviceToHost);
    RS[RS_len] = '\0';

    printf("Output RS: %s\n", RS);

    cudaFree(d_S);
    cudaFree(d_RS);
    free(RS);
    return 0;
}