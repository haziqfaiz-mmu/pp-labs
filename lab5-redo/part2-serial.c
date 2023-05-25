#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int numprocs, namelen, rank,size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int interval;
    double localResult,result;

    double f(double x){
        return (4/(1+x*x));
    }

    double pi(int interval){
        double step = 1.0/interval;
        double x; double total=0; int i;

        for(int i=0;i<interval;i++){
            x=(step/2) + step*i;
            total = total+f(x);
        }
        return total*step;
    }

    printf("\nEnter number of intervals: ");
    fflush(stdout);
    scanf("%d", &interval);
    printf("Number of intervals is %d",interval);
    result = pi(interval);

    printf("\nPi is %1.20f using %d intervals",result,interval);
    
    
}