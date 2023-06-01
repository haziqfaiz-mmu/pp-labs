#include <stdio.h> 
#include <omp.h>
 
int main() { 
    int i,tnum; 
    int x=6;
    printf("Hello World\n"); 
    
    #pragma omp parallel for shared(x,tnum)
    for(i=0;i<x;i++){
        tnum = omp_get_thread_num(); 
        printf("Iter:%d from thread %d\n",i,tnum); 
    }
    
 
    printf("GoodBye World\n"); 
} 