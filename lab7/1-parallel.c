#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <mpi.h>
 
#define BUFSIZE 256 
 
int main(int argc, char *argv[]) {
    int *data, result; 
    int size, i; 
    int eachSize, eachResult, *eachData;
    FILE *infile; 
    char buf[BUFSIZE]; 
    int numprocs, namelen, rank,psize;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
        
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size (MPI_COMM_WORLD, &psize);
    MPI_Get_processor_name(processor_name,&namelen);

    
    if(!rank){
        //printf("What is the name of the data file?\n"); 
        //fgets(buf,BUFSIZE,stdin); 
        //buf[strlen(buf)-1]='\0'; // Remove the carriage return from the file name 
        strncpy(buf, "lab07dat1.txt", 100);

        infile = fopen(buf,"r"); 
        if (infile==NULL) { 
            perror ("Opening file"); 
            exit(1); 
        } 
        fscanf(infile,"%d", &size); // Find out how big the data is 
        printf("Size = %d\n",size); 
        eachSize=size/4 +1;
        
    }
    //Broadcast each size
    MPI_Bcast(&eachSize,1,MPI_INT,0,MPI_COMM_WORLD); 
    
    // Read the data in process 0
    if(!rank){
        data = (int *)malloc(sizeof(int)*size); // Allocate the space for original data
        for (i=0; i<size; i++){
        fscanf(infile,"%d",&data[i]); 
        //printf("%d ",data[i]);  
        } 
    }
    eachData = (int *)malloc(sizeof(int)*eachSize); // Allocate the space 
    //Then scatter data to each process
    MPI_Scatter(data,eachSize,MPI_INT,eachData,eachSize,MPI_INT,0,MPI_COMM_WORLD);
    
    
    //Actual calculation happen here
    eachResult = 0; 
    for (i=0; i<eachSize; i++) 
    eachResult += eachData[i];
    for(int i=0;i<psize;i++){
        if(i==rank){
            //printf("\nResult process %d: %d\n",rank,result); 
            printf("\nSize process %d: %d\n",rank,eachSize);
            printf("\nResult process %d: %d\n",rank,eachResult);
        }
    }

    MPI_Reduce(&eachResult,&result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(!rank){
        printf("\nResult: %d\n",result);
    }
    

    MPI_Finalize();
}