#include <mpi.h>
#include <stdio.h>
#define BUFSIZE 256

int main(int argc, char *argv[]) {
  int numprocs, rank, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int x,y,z;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);
  MPI_Status status;
  for (int i=0;i<3;i++){
    switch (i) {
    case 0:
      x = 0;
      y = 1;
      z = 2;
      MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
      MPI_Send(&y, 1, MPI_INT, 2, 43, MPI_COMM_WORLD);
      MPI_Bcast(&z, 1, MPI_INT, 1, MPI_COMM_WORLD);
      break;
    case 1:
      x = 3;
      y = 4;
      z = 5;
      MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
      MPI_Bcast(&y, 1, MPI_INT, 1, MPI_COMM_WORLD);
      break;
    case 2:
      x = 6;
      y = 7;
      z = 8;
      MPI_Bcast(&z, 1, MPI_INT, 0, MPI_COMM_WORLD);
      MPI_Recv(&x, 1, MPI_INT, 0, 43, MPI_COMM_WORLD, &status);
      MPI_Bcast(&y, 1, MPI_INT, 1, MPI_COMM_WORLD);
      break;
    }
    printf("%d: x=%d y=%d z=%d\n", rank, x, y, z);
  }

  MPI_Finalize();
}

// Ansswe
//  p0 x=0, y=1, z=4
// p1 x=0, y=4, z=5
// p2 x=1, y=4, z=0
