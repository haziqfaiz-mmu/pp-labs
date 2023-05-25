#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
#define BUFSIZE 256 
 
int main(int argc, char *argv[]) {
  int *data, result; 
  int size, i; 
  FILE *infile; 
  char buf[BUFSIZE]; 
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
  data = (int *)malloc(sizeof(int)*size); // Allocate the space 
  // Read the data
  for (i=0; i<size; i++){
    fscanf(infile,"%d",&data[i]); 
    printf("%d ",data[i]);  
  } 
  result = 0; 
  for (i=0; i<size; i++) 
    result += data[i]; 
  printf("\nResult: %d\n",result); 
}