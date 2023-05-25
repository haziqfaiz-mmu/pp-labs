//trapezoidal 
#include<stdio.h> 
#include<math.h> 
 
double f(double x){ 
 return (sin (x/2) +1); 
} 
 
int main(){ 
 
 double a,b,w,sum=0,y[2]; 
 int i,n; 
 //double M_PI = 3.14159265359;
 
 printf("Enter the number of intervals : "); 
 scanf("%d",&n); 
  
 a=M_PI/2; 
 b=2*M_PI; 
 
 //step length (width of each trapezoid) 
 w=(b-a)/n; 
 // Initialize the heights 
 y[0]= f(a); 
 
 for(i=1; i<=n; i++) 
 { y[i%2] = f(a+i*w); 
  sum += y[i%2] + y[(i+1)%2]; 
 } 
 // Multiply with half the width. 
 sum = sum * w/2; 
  
 printf("Answer : %f \n",sum); 
 
 return 0; 
}