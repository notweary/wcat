/*Custom cat program
Constraints: fopen(), fgets(), and fclose()
Can take multiple arguments
works on very simple text files, as far as i know/(have tried) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

int main(int argc, char** argv){

    for(int i = 1; i < argc; i++){

	FILE *fp = fopen(argv[i], "rb"); 

	//check if file or directory exists
	if (fp == NULL){
	    char *er = strerror(errno);
	    printf("%s\n", er);
	    exit(1);
	}

	//determine size of file
	int fs = fseek(fp,0,SEEK_END);
	if (fs == -1){//error 
	    char *er = strerror(errno);
	    printf("%s\n", er);
	    fclose(fp);
	    exit(1);
	}

	long size= ftell(fp); 
	if (size == -1L){//error 
	    char *er = strerror(errno);
	    printf("%s\n", er);
	    fclose(fp);
	    exit(1);
	}

	if (size == 0 || size >= PTRDIFF_MAX){
	    //avoid malloc(0) or allocating more than PTRDIFF_MAX
	    fclose(fp);
	    exit(1);
	}

	//for condition used in do-while
	long pos;
	
	//dynamic array 
	char *buffer = malloc(size+1);
	if (buffer == NULL){
	    fclose(fp);
	    exit(1);
	}
	//reset file position indicator of stream (fp)
	rewind(fp);

	while(fgets(buffer,(size+1),fp) != NULL){
	    printf("%s",buffer);
	}

	
	int f_c = fclose(fp);
	free(buffer);
    }
    return 0;
}
