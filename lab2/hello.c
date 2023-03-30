#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
  int numprocs, rank, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);
  printf("Process %d on %s out of %d\n", rank, processor_name, numprocs);
  MPI_Finalize();
}
/* ANSWERS
   1.  fs

   2. MPI_Init(&argc, &argv) to initialize
      MPI_FInalize() to end
   3. Creates a global communicator that encapsulates every single process of the current run.
   4. Unique ID assigned to each process.
 */
