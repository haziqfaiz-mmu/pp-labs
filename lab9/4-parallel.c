#include <stdio.h> 
#include <math.h> 
#include <omp.h>
 
#define START (M_PI/2) 
#define END (M_PI*2) 
 
double f(double x) { 
    return sin(x/2)+1; 
} 
 
int main(int argc, char *argv[]) { 
    double total = 0, x; 
    int partitions; 
    double slice; 

    //omp_set_num_threads(4);

    printf("How many partitions? "); fflush(stdout); 
    scanf("%d", &partitions); 
    slice = (END-START)/partitions; 

    #pragma omp parallel  for reduction (+:total) //private(x)
    for(int i=0;i<partitions;i++){
        //#pragma omp parallel private(x)
        x= START  + (slice/2) + (slice*i);
        printf("\n x is %f f(x) is %f",x,f(x));
        total=total+f(x);
    }
    total = total*slice;

    printf("\nThe integration is %1.10f\n", total); 
}