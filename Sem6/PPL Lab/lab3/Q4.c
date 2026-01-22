#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, len;
    char s1[100], s2[100];
    char r1[20], r2[20], sub[40], res[200];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        printf("Enter string S1: ");
        scanf("%s", s1);
        printf("Enter string S2: ");
        scanf("%s", s2);
        len = strlen(s1);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(s1, len/size, MPI_CHAR, r1, len/size, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(s2, len/size, MPI_CHAR, r2, len/size, MPI_CHAR, 0, MPI_COMM_WORLD);

    int k = 0;
    for(int i = 0; i < len/size; i++)
    {
        sub[k++] = r1[i];
        sub[k++] = r2[i];
    }

    MPI_Gather(sub, 2*(len/size), MPI_CHAR,
               res, 2*(len/size), MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        res[2*len] = '\0';
        printf("Resultant string = %s\n", res);
    }

    MPI_Finalize();
    return 0;
}
