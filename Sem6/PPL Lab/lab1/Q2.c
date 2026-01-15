#include<mpi.h>
#include<stdlib.h>
#include<math.h>
int main(int argc, char* argv[]){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int a=10000,b=100;
    int res;
    switch(rank){
        case 0: res=a+b;
                printf("Addition Process \t Result = %d\n",res);
                break; 
        case 1: res=a-b;
                printf("Sub Process \t Result = %d\n",res);
                break; 
        case 2: res=a*b;
                printf("product Process \t Result = %d\n",res);
                break; 
        case 3: res=a/b;
                printf("division Process \t Result = %d\n",res);
                break;        
        default: printf("Default Case");        
    }
    MPI_Finalize();

}