#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size, M;
    float A[100], sub[20], avg, avg_all[10], total = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        printf("Enter M (elements per process): ");
        scanf("%d", &M);

        printf("Enter %d elements:\n", M * size);
        for(int i = 0; i < M * size; i++)
            scanf("%f", &A[i]);
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(A, M, MPI_FLOAT, sub, M, MPI_FLOAT, 0, MPI_COMM_WORLD);

    avg = 0;
    for(int i = 0; i < M; i++)
        avg += sub[i];
    avg /= M;

    MPI_Gather(&avg, 1, MPI_FLOAT, avg_all, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        for(int i = 0; i < size; i++)
            total += avg_all[i];

        printf("Total Average = %f\n", total / size);
    }

    MPI_Finalize();
    return 0;
}
