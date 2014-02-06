#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#include "../include/structures.h"


/*
 *  This function parses the specification file and stores the data in the task structure.
 */
void parse_specs(struct task_list* task, char* filename)
{
	FILE*	fp;							// File Pointer to access the spec file
	char*	data;							// Stores the ptr returned by the strtok
	char*  	filepath = "../test/";					// Path of the spec file 
	char*	fullfilename 	= (char*)malloc(sizeof(char)*100);	//  Will hold the sull path of the file
	char* 	readline	= (char*)malloc(sizeof(char)*200);	// Stores the 1 line from the spec file

	struct  task_struct_t*	ptask 	=	NULL;			// To create the periodic task
	struct 	task_struct_t*	ptmp	=	NULL;			// To hold the last position in the linked list
	struct 	activities*	act	=	NULL;			// To create the activity
	
	int 	task_num;
	int 	i;
	size_t	n;
	
	
	// Creating the full path name
	strcpy(fullfilename,filepath);
	strcat(fullfilename,filename);


	// Opening the file for reading , if any problem exit the program
	fp = fopen((const char*)fullfilename , "r");
	if(fp == NULL)
	{
		printf("Error opening the file : %s \n",filename);
		printf("Error : %s \n",strerror(errno));
		exit(1);
	}

		
	// Reading the first line 
	getline(&readline,&n,fp);


	// Extracting the num of tasks and total time of execution
	sscanf(readline,"%d %d",&task_num,&task->total_time);


	// Reading task_num lines from the file to fill the data	
	for(i = 0; i < task_num;i++)
	{
		getline(&readline,&n,fp);

		ptask = (struct task_struct_t*)malloc(sizeof(struct task_struct_t));
		ptask->start 	= NULL;
		ptask->currpos	= NULL;
		ptask->next	= NULL;

		// Extracting the first token
		data = strtok(readline," ");

		if(data[0] == 'P')
			ptask->task_type = 'P';
		else
			ptask->task_type = 'A';

		// Adding the task to the  task linked list		
		if(task->head == NULL)
		{
			task->head = ptask;
			ptmp = ptask;
		}
		else
		{
			ptmp->next = ptask;
			ptmp = ptask;
		}

		// Extracting the period 
		data = strtok(NULL," ");
		ptask->period_event = atoi(data);

		// Extracting the priority
		data = strtok(NULL," ");
		ptask->priority = atoi(data);

		// Extracting the Body of the task
		data = strtok(NULL," ");
		while(data != NULL)
		{
			act = (struct activities*)malloc(sizeof(struct activities));
			act->next = NULL;
			if(data[0] >= '0' && data[0] <= '9') {
				act->work = atoi(data);	
				act->type = 'C';
			}
			else if(data[0] == 'L') {
				sscanf(data,"L(%d)",&act->work);
				act->type = 'L';
			}
			else if(data[0] == 'U') {
				sscanf(data,"U(%d)",&act->work);
				act->type = 'U';
			}

			// Adding activity one at a time
			if(ptask->start == NULL){
				ptask->start = act;
				ptask->currpos = act;
			}
			else {
				ptask->currpos->next = act;
				ptask->currpos	     = act;
			}
			

			data = strtok(NULL, " ");
		}
		ptask->currpos = ptask->start;
			

	}



	// Deallocating the memory
	if(readline)
		free(readline);
	if(fullfilename)
		free(fullfilename);

	fclose(fp);
}
