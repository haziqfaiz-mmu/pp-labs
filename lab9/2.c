#include <stdio.h> 
#include <omp.h>

float dot_prod(float* a, float* b, int N) 
{ 
  float sum = 0.0; 
#pragma omp parallel for reduction(+:sum) 
   for(int i=0; i<N; i++) { 
     sum += a[i] * b[i]; 
   } 
  return sum; 
} 
  
int main() { 
   float a[5] ={1,2,3,4,5};
   float b[5] = {6,7,8,9,10};
   int N=5;

   float result= dot_prod(a,b,N);
   printf("\nResult = %f",result);
} 