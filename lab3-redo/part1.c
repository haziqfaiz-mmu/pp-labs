#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int numprocs, namelen, rank;
    char processor_name[MPI_MAX_PROCESSOR_NAME];


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Get_processor_name(processor_name,&namelen);

    if (rank!=0){
        MPI_Send(&rank,1,MPI_INT,0,100,MPI_COMM_WORLD);
    }

    else{
        for(int i=1;i<numprocs;i++){
            MPI_Recv(&rank,1,MPI_INT,i,100,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("Current rank is %d\n",rank);
        }
    }

    MPI_Finalize();
}