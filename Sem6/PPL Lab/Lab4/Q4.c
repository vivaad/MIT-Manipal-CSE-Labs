#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char word[100], ch;
    char local[100], result[500] = "";

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter word: ");
        scanf("%s", word);
    }

    MPI_Scatter(word, 1, MPI_CHAR, &ch, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    int k = 0;
    for (int i = 0; i <= rank; i++)
        local[k++] = ch;
    local[k] = '\0';

    MPI_Gather(local, 100, MPI_CHAR, result, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Output: ");
        for (int i = 0; i < size; i++)
            printf("%s", result + i * 100);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

