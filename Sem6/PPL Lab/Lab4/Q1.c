#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    int f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}

int main(int argc, char *argv[]) {
    int rank, size, fact, scan_sum;
    int err;
    char err_string[MPI_MAX_ERROR_STRING];
    int err_len;

    MPI_Init(&argc, &argv);

    err = MPI_Comm_rank(MPI_COMM_NULL, &rank);
    if (err != MPI_SUCCESS) {
        MPI_Error_string(err, err_string, &err_len);
        printf("MPI_Comm_rank error: %s\n", err_string);
        MPI_Abort(MPI_COMM_WORLD, err);
    }

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    fact = factorial(rank + 1);

    err = MPI_Scan(&fact, &scan_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    if (err != MPI_SUCCESS) {
        MPI_Error_string(err, err_string, &err_len);
        printf("MPI_Scan error: %s\n", err_string);
        MPI_Abort(MPI_COMM_WORLD, err);
    }

    if (rank == size - 1) {
        printf("Sum of factorials from 1! to %d! = %d\n", size, scan_sum);
    }

    MPI_Finalize();
    return 0;
}
