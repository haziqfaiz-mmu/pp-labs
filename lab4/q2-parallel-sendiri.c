
#include<stdio.h>
#include<math.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
int rank,size;
MPI_Init(&argc, &argv);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
MPI_Comm_size (MPI_COMM_WORLD, &size);

long int i, n;
double sum=0.0, term, pi,total_sum=0.0;
printf("Enter number of terms: ");
scanf("%ld", &n);

/* Applying Leibniz Formula */
for(i=rank;i< n;i+=size)
{
    term = pow(-1, i) / (2*i+1);
    sum += term;
}
MPI_Reduce(&sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
pi = 4 * total_sum;

printf("\nPI = %.6lf", pi);
MPI_Finalize();
 
return 0;
}
