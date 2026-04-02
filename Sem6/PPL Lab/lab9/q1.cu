// csr_spmv_input.cu
#include <stdio.h>
#include <cuda.h>

__global__ void spmv(int *data, int *col_index, int *row_ptr, int *x, int *y, int rows) {
    int row = threadIdx.x + blockIdx.x * blockDim.x;

    if (row < rows) {
        int sum = 0;
        for (int j = row_ptr[row]; j < row_ptr[row + 1]; j++) {
            sum += data[j] * x[col_index[j]];
        }
        y[row] = sum;
    }
}

int main() {
    int rows, cols;

    printf("Enter rows and cols: ");
    scanf("%d %d", &rows, &cols);

    int A[100][100], x[100];

    printf("Enter matrix:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &A[i][j]);

    printf("Enter vector:\n");
    for (int i = 0; i < cols; i++)
        scanf("%d", &x[i]);

    // Convert to CSR
    int data[100], col_index[100], row_ptr[100];
    int k = 0;

    row_ptr[0] = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (A[i][j] != 0) {
                data[k] = A[i][j];
                col_index[k] = j;
                k++;
            }
        }
        row_ptr[i + 1] = k;
    }

    int *d_data, *d_col, *d_row, *d_x, *d_y;
    int y[100];

    cudaMalloc(&d_data, k * sizeof(int));
    cudaMalloc(&d_col, k * sizeof(int));
    cudaMalloc(&d_row, (rows + 1) * sizeof(int));
    cudaMalloc(&d_x, cols * sizeof(int));
    cudaMalloc(&d_y, rows * sizeof(int));

    cudaMemcpy(d_data, data, k * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_col, col_index, k * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_row, row_ptr, (rows + 1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, cols * sizeof(int), cudaMemcpyHostToDevice);

    spmv<<<1, rows>>>(d_data, d_col, d_row, d_x, d_y, rows);
 
    cudaMemcpy(y, d_y, rows * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Result:\n");
    for (int i = 0; i < rows; i++)
        printf("%d ", y[i]);

    return 0;
}