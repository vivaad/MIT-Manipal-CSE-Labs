// word_count_atomic
#include <stdio.h>
#include <string.h>

__global__ void countWord(char *sentence, char *word, int *count, int slen, int wlen) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx <= slen - wlen) {
        int match = 1;
        for (int i = 0; i < wlen; i++) {
            if (sentence[idx + i] != word[i]) {
                match = 0;
                break;
            }
        }
        if (match)
            atomicAdd(count, 1);
    }
}

int main() {
    char sentence[200], word[50];
    int *d_count, count = 0;
    char *d_sentence, *d_word;

    printf("Enter sentence: ");
    fgets(sentence, 200, stdin);
    printf("Enter word to search: ");
    scanf("%s", word);

    int slen = strlen(sentence);
    int wlen = strlen(word);
    cudaMalloc(&d_sentence, slen);
    cudaMalloc(&d_word, wlen);
    cudaMalloc(&d_count, sizeof(int));
    
    cudaMemcpy(d_sentence, sentence, slen, cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, wlen, cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

    countWord<<<(slen+255)/256, 256>>>(d_sentence, d_word, d_count, slen, wlen);
    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);
    printf("Word repeated %d times\n", count);
    cudaFree(d_sentence);
    cudaFree(d_word);
    cudaFree(d_count);
    return 0;
}