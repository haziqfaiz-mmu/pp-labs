#include <mpi.h>
#include <stdio.h>
#define BUFSIZE 256

int main(int argc, char *argv[]) {
  int numprocs, rank, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  char buf[BUFSIZE];
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);
  sprintf(buf,"Process %d out of %d\n",rank,numprocs);

  MPI_Send(buf, BUFSIZE, MPI_CHAR, 0, 1, MPI_COMM_WORLD);

  if(rank==0){
    for (int i=0; i<numprocs; i++) {
      MPI_Recv(buf, BUFSIZE, MPI_CHAR, i, 1, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
      printf(buf);
        }
  }

  MPI_Finalize();
}
