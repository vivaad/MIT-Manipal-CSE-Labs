#include <mpi.h>
#include <stdio.h>

int fact(int x)
{
    int f = 1;
    for(int i = 1; i <= x; i++)
        f *= i;
    return f;
}

int main(int argc, char *argv[])
{
    int rank, size, A[10], B[10], x, sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        printf("Enter %d values:\n", size);
        for(int i = 0; i < size; i++)
            scanf("%d", &A[i]);
    }

    MPI_Scatter(A, 1, MPI_INT, &x, 1, MPI_INT, 0, MPI_COMM_WORLD);

    x = fact(x);

    MPI_Gather(&x, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        for(int i = 0; i < size; i++)
            sum += B[i];

        printf("Sum of factorials = %d\n", sum);
    }

    MPI_Finalize();
    return 0;
}
