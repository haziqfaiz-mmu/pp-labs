//trapezoidal 
#include<stdio.h> 
#include<math.h> 
#include<mpi.h>
 
double f(double x){ 
 return (sin (x/2) +1); 
} 
 
int main(int argc, char *argv[]){ 
 
    double a,b,w,sum=0,y[2],localSum=0; 
    int i,n; 
    int numprocs, namelen, rank,size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(processor_name,&namelen);
    a=M_PI/2; 
    
    b=2*M_PI; 
   
    if(!rank){
        printf("Enter the number of intervals : "); 
        fflush(stdout);
        scanf("%d",&n); 
        //step length (width of each trapezoid) 
        w=(b-a)/n; 
    }

    MPI_Bcast(&w,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
    
    // Initialize the heights 
    int div=n/size;
    y[0]= f(a+w*div*rank); 
    
    for(i=div*rank; i<div*(rank+1); i++) {
        y[i%2] = f(a+i*w); 
        localSum += y[i%2] + y[(i+1)%2]; 
    } 
    // Multiply with half the width. 
    localSum = localSum * w/2; 

    MPI_Reduce(&localSum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    //sum = sum +f(a+w*(n-1));

    //printf("\nlocal sum : %f \n",localSum);
    for(i=0;i<size;i++){
        if(i==rank){
            printf("\nStarting for rank %d: %d",rank,div*rank);
            printf("\nEnding for rank %d: %d\n",rank,div*(rank+1));
        }
    }
   
    if(!rank){
        printf("\nAnswer : %f \n",sum); 
    }

    MPI_Finalize();
    
    return 0; 
}