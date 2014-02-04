#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "../include/structures.h"


int main(int argc,char** argv)
{
	char* filename;
	struct task_list tasks;
	

	/* If you do not enter the filename or add more than 1 agruments */
	if(argc != 2)
	{
		printf("Usage: ./tasks <filename> \n");
		printf("File should be present in the test folder \n");
		return 1;
	}


	filename = (char*)malloc(sizeof(char)*30);
	strcpy(filename,argv[1]);
	printf("Filename = %s \n",filename);
	

	// Parse the specification file
	parse_specs(&tasks,filename);




	if(!filename)
		free(filename);

	return 0;
}
