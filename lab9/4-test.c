#include <stdio.h> 
#include <math.h> 
#include <omp.h>
 
#define START (M_PI/2) 
#define END (M_PI*2) 
 
double f(double x) { 
    return sin(x/2)+1; 
} 
 
int main(int argc, char *argv[]) { 

double slice = (END-START)/10; 
double total,val;

for(int i=0;i<10;i++){
    printf("start is %f\n",START  + (slice/2) + (slice*i));
    val=f(START  + (slice/2) + (slice*i));
    printf("f(x) is %f\n",val);
    total =total+val;
}
total=total*slice;


printf("total is %f",total);


}