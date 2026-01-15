#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[]){
    
    int rank,size;
    int i;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    if(rank==0){
        for(int j=1;j<4;j++){
            MPI_Send(&i,1,MPI_INT,j,j,MPI_COMM_WORLD);
            printf("Sent Process %d message %d\n",i,i);
        }
    }else{
        printf("hello\n");
        MPI_Recv(&i,1,MPI_INT,0,rank,MPI_COMM_WORLD,&status);
        printf("Recieved message from master process : %d\n",i);
    }

    MPI_Finalize();

}