#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mpi.h>
#define BUFSIZE 256

int main(int argc, char *argv[]){ 
    int i, size;
    char filename[BUFSIZE];
    FILE *outfile;
    int numprocs, namelen, rank,psize;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int *array,*localArray;
        
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size (MPI_COMM_WORLD, &psize);
    MPI_Get_processor_name(processor_name,&namelen);

    if(!rank){
        //printf("What is the file name you want to write to? ");
        //scanf("%s", filename);
        strncpy(filename, "question 2.txt", 100);
        //printf("How many long integers to generate? ");
        //scanf("%d", &size);
        size = 10000;
        outfile = fopen(filename,"w");
        if (!outfile)
        { fprintf(stderr,"Unable to open %s for writing.\n", filename);
        exit(1);
        }
        fprintf(outfile,"%d\n",size);
    }
    
    //int localArray[size/4];
    localArray = (int *)malloc(sizeof(int)*size/4);
    //int array[size];
    array = (int *)malloc(sizeof(int)*size);
    srandom(time(0));
    for (int i=0; i<size/4; i++){
        
        localArray[i] = random();
    }
    MPI_Gather(localArray,size/4,MPI_INT,array,size/4,MPI_INT,0,MPI_COMM_WORLD);

    if(!rank){
        for (int i=0; i<size; i++){
            printf("%d ",array[i]);
            //fprintf(outfile,"%ld\n", array[i]);
        }
        fclose(outfile);
    }
    
    MPI_Finalize();
}