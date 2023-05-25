#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define BUFSIZE 256

int xsize, ysize, maxIteration;
double cx, cy, xscale, xoffset, yscale, yoffset;

int julia(int x, int y)
{ double zx = (double)x/xsize *xscale -xoffset;
  double zy = (double)y/ysize *yscale -yoffset;
  
  int iteration = 0;
  
  while((iteration<maxIteration) && (zx * zx + zy * zy < 4))
  {
	  double xtemp = zx * zx - zy * zy;
	  zy = 2 * zx * zy + cy;
	  zx = xtemp + cx;
	  
	  iteration++;
  }
  
  return iteration;
}

int main(int argc, char*argv[]){

MPI_Init(&argc, &argv);
//Get process ID
int rank, size, error, i;
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
//Get processes Number
MPI_Comm_size (MPI_COMM_WORLD, &size);
    
//Synchronize all processes and get the begin time
MPI_Barrier(MPI_COMM_WORLD);
//begin = MPI_Wtime();
int x, y;
int **picture;
char buff[BUFSIZE];
FILE *outfile;

strncpy(buff,"julia-parallel-scatter.pgm",BUFSIZE);
xsize=1920; ysize=1080; xscale=3.5; xoffset=1.7; yscale=2.0; yoffset=1.0;
cx=-0.79; cy=0.15; maxIteration=512;


printf("Program to generate a Julia fractal\n");
//printf("What file should I store the picture in? [E.g. julia.pgm] ");fflush(stdout);
//fgets(buff,BUFSIZE,stdin); buff[strlen(buff)-1]=0; // Remove the ending line feed
//printf("How wide and tall should the picture be? [E.g. 1920 1080] ");fflush(stdout);
//scanf("%d %d", &xsize, &ysize);
//printf("What is the x scale and x offset? [E.g. 3.5 1.7] ");fflush(stdout);
//scanf("%lf %lf", &xscale, &xoffset);  
//printf("What is the y scale and y offset? [E.g. 2.0 1.0] ");fflush(stdout);
//scanf("%lf %lf", &yscale, &yoffset);   
//printf("What are the x and y components of the Julia constant? [E.g -0.79 0.15] ");fflush(stdout);
//scanf("%lf %lf", &cx, &cy);
//printf("How many times to iterate? [E.g. 512] "); fflush(stdout);
//scanf("%d", &maxIteration);

if(rank==0){
    picture =(int**)malloc(sizeof(int*)*ysize);
    for (int i = 0; i < xsize; i++) {
        for (int j = 0; j < ysize; j++) {
            picture[i*4 + j] = i*4 + j;
        }
    }
}

//create a buffer that will hold a subset of the picture array
int **sub_picture= (int**)malloc(sizeof(int*)*ysize);

//scatter the picture array
int elements_per_proc = y/4;
MPI_Scatter(picture, elements_per_proc, MPI_INT, sub_picture,
            elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

for (y=0; y<elements_per_proc; y++){
    sub_picture[y] = (int*)malloc(sizeof(int)*xsize);
    for (x=0; x<xsize; x++)
            sub_picture[y][x] = julia(x,y);
}

MPI_Gather(&picture, 1, MPI_INT, sub_picture, 1, MPI_INT, 0,
           MPI_COMM_WORLD);
if(rank==0){
    outfile=fopen(buff,"w");
    fprintf(outfile,"P2\n%d %d %d\n",xsize, ysize, maxIteration);
    for(y=0; y<ysize; y++)
        for (x=0; x<xsize; x++)
            fprintf(outfile,"%d\n", picture[y][x]);
}
fclose(outfile);

MPI_Finalize();
}
