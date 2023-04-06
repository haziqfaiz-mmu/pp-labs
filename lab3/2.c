#include <mpi.h>
#include <stdio.h>
#define BUFSIZE 256

int main(int argc, char *argv[]) {
  int numprocs, rank, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  char buf[BUFSIZE];
  int input=0;

  printf("Enter a number: ");
  scanf("%d",&input);
  

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);
  //sprintf(buf,"Process %d out of %d\n",rank,numprocs);
  
  //MPI_Send(buf, BUFSIZE, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
  
  
  //MPI_Barrier(MPI_COMM_WORLD);
  while(input>-1){
    fflush(stdout);
    if(rank==0){ 
      printf("Enter a number: ");
      fflush(stdout);
      scanf("%d",&input);
      fflush(stdout);
      //printf("Input = %d Process = %d\n",input,rank);
    }
    //MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&input,1,MPI_INT,0,MPI_COMM_WORLD);
    //MPI_Barrier(MPI_COMM_WORLD);
    printf("Input = %d Process = %d\n",input,rank);
    fflush(stdout);
     
  }
 
  
  

  MPI_Finalize();
}
