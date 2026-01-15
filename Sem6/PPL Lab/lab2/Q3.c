#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size,n,buffer_size;
    char *buffer;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    buffer_size = (sizeof(int) + MPI_BSEND_OVERHEAD) * (size - 1);
    buffer = (char *)malloc(buffer_size);

    MPI_Buffer_attach(buffer, buffer_size);
    if (rank == 0) {
        int arr[size];
        printf("Enter %d elements:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
        for (int i = 1; i < size; i++) {
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    else {
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        if (rank % 2 == 0)
            printf("Process %d received %d, Square = %d\n",
                   rank, n, n * n);
        else
            printf("Process %d received %d, Cube = %d\n",
                   rank, n, n * n * n);
    }
    MPI_Buffer_detach(&buffer, &buffer_size);
    MPI_Finalize();
}
