#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int numprocs, namelen, rank;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Get_processor_name(processor_name,&namelen);

    int data=88;    
    printf("Before broadcast:\n");
    for(int i=0;i<numprocs;i++){
        if(i==rank)
            printf("Rank %d data is %d\n",rank,data);
    }
    if(rank==0){
            data=99;
            MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);
        }
    MPI_Barrier(MPI_COMM_WORLD);
    printf("After broadcast:\n");
    for(int i=0;i<numprocs;i++){
        if(i==rank)
            printf("Rank %d data is %d\n",rank,data);
    }

    MPI_Finalize();
}