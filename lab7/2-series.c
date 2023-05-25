#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define BUFSIZE 256

int main(){ 
    int i, size;
    char filename[BUFSIZE];
    FILE *outfile;

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
    srandom(time(0));
    for (i=0; i<size; i++){
        fprintf(outfile,"%ld\n", random());
    }
    fclose(outfile);
}