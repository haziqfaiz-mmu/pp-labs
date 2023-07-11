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

    int numprocs, namelen, rank,size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int interval;
    double localResult,result;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(processor_name,&namelen);

    int x, y;
    int **picture,**localPicture;
    char buff[BUFSIZE];
    FILE *outfile; 
    //Rank 0 read input
    if (rank==0){
        printf("Program to generate a Julia fractal\n");
        printf("What file should I store the picture in? [E.g. julia.pgm] ");fflush(stdout);
        fgets(buff,BUFSIZE,stdin); buff[strlen(buff)-1]=0; // Remove the ending line feed
        printf("How wide and tall should the picture be? [E.g. 1920 1080] ");fflush(stdout);
        scanf("%d %d", &xsize, &ysize);
        printf("What is the x scale and x offset? [E.g. 3.5 1.7] ");fflush(stdout);
        scanf("%lf %lf", &xscale, &xoffset);  
        printf("What is the y scale and y offset? [E.g. 2.0 1.0] ");fflush(stdout);
        scanf("%lf %lf", &yscale, &yoffset);   
        printf("What are the x and y components of the Julia constant? [E.g -0.79 0.15] ");fflush(stdout);
        scanf("%lf %lf", &cx, &cy);
        printf("How many times to iterate? [E.g. 512] "); fflush(stdout);
        scanf("%d", &maxIteration);    

    }   

    //Broadcast xsize, ysize, xsale, xoffset, yscale,yoffset,cx,cy and maxIteration
    MPI_Bcast(&xsize,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&ysize,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&maxIteration,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&xscale,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&xoffset,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&yscale,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&yoffset,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&cx,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&cy,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

    int chunkSize=ysize/size;

    
    picture =(int**)malloc(sizeof(int*)*ysize);    
    for (y=rank; y<ysize; y++)
        { 
            picture[y] = (int*)malloc(sizeof(int)*xsize);
            for (x=0; x<xsize; x++)
                picture[y][x] = julia(x,y);
    }

   
    if(!rank){
    outfile=fopen(buff,"w");
    fprintf(outfile,"P2\n%d %d %d\n",xsize, ysize, maxIteration);
    for(y=0; y<ysize; y++)
        for (x=0; x<xsize; x++)
            fprintf(outfile,"%d\n", localPicture[y][x]);

    fclose(outfile);

    }
    
    MPI_Finalize();
}
