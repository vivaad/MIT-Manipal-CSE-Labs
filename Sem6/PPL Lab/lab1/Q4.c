#include<mpi.h>
#include<stdlib.h>
#include<math.h>

int factorial(int n) {
   if(n == 0) {
      return 1;
   } else {
      return n * factorial(n-1);
   }
}

int fib(int n) {
   if(n == 0){
      return 0;
   } else if(n == 1) {
      return 1;
   } else {
      return (fib(n-1) + fib(n-2));
   }
}



int main(int argc, char* argv[]){
    int rank, size, res;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if((rank%2)!=0){
        res = fib(rank);
        printf("Result of process %d in fib is %d\n",rank,res);
    }
    else{
        res = factorial(rank);
        printf("Result of process %d in factorial is %d\n",rank,res);        
    }
        
    MPI_Finalize();

}