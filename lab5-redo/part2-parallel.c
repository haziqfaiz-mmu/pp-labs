#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int numprocs, namelen, rank,size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int interval;
    double localResult,result;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(processor_name,&namelen);

    double f(double x){
        return (4/(1+x*x));
    }

    double pi(int interval,int rank,int size){
        double step = 1.0/interval;
        double x; double total=0; int i;

        for(int i=rank+1;i<interval;i=i+size+1){
            x=(step/2); + step*i;
            total = total+f(x);
        }
        return total*step;
    }

    
    if(rank==0){
        printf("\nEnter number of intervals: ");
        fflush(stdout);
        scanf("%d", &interval);
        printf("Number of intervals is %d",interval);
    }    
    double start = MPI_Wtime();

    MPI_Bcast(&interval,1,MPI_INT,0,MPI_COMM_WORLD);
    localResult=pi(interval,rank,size);
    MPI_Reduce(&localResult,&result,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    double end = MPI_Wtime();


    if(!rank){
        printf("\nPi is %1.20f using %d intervals",result,interval);
        printf("\nElapsed time is %f",end-start);
    }
    MPI_Finalize();
}