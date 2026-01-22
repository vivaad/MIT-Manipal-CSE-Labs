#include <mpi.h>
#include <stdio.h>
#include <string.h>

int isVowel(char c)
{
    return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
            c=='A'||c=='E'||c=='I'||c=='O'||c=='U');
}

int main(int argc, char *argv[])
{
    int rank, size, len;
    int count = 0, counts[10];
    char str[100], sub[20];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        printf("Enter string: ");
        scanf("%s", str);
        len = strlen(str);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(str, len/size, MPI_CHAR,
                sub, len/size, MPI_CHAR, 0, MPI_COMM_WORLD);

    for(int i = 0; i < len/size; i++)
        if(!isVowel(sub[i]))
            count++;

    MPI_Gather(&count, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        int total = 0;
        for(int i = 0; i < size; i++)
            total += counts[i];

        printf("Total non-vowels = %d\n", total);
    }

    MPI_Finalize();
    return 0;
}
