#include<mpi.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char* argv[]){
    int x = 15;
    int rank, size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank != 0){
        int res = pow(x,rank);
        printf("%d\n",res);
    }else{
        printf("Rank is 0\n");
    }

    if((rank%2)==0){
        printf("Hello\n");   
    }else{
        printf("World\n");
    }
        
    MPI_Finalize();
    return 0;	
}
