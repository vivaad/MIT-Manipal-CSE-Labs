#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size, value;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (rank == 0) {
        printf("Enter an integer: ");
        fflush(stdout);
        scanf("%d", &value);

        printf("Sending %d to Rank 1\n", value);
        value++; 
        MPI_Ssend(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received back value %d from Rank %d\n", value, size - 1);

    } else {

        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        printf("Process %d - Received %d, incrementing and sending...\n", rank, value);
        value++;
        int dest = (rank == size - 1) ? 0 : rank + 1;
                
        MPI_Ssend(&value, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}