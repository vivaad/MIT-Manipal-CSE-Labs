#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[]){
    int rank=6,size=-1;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    MPI_Status status;
    
    char word[100];
    if(rank==0){
        printf("Enter string : ");
        scanf("%s",word);
        MPI_Ssend(word,100,MPI_CHAR,1,1,MPI_COMM_WORLD);
        
        //waiting for a recv

        MPI_Recv(word,100,MPI_CHAR,1,2,MPI_COMM_WORLD,&status);

        printf("After Sync. Sending : %s\n",word);
    }else{
        MPI_Recv(word,100,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);

        for(int i=0;i<strlen(word);i++){
            word[i]^=32;
        }
        MPI_Ssend(word,100,MPI_CHAR,0,2,MPI_COMM_WORLD);
    }
    

    MPI_Finalize();
    return 0;
}