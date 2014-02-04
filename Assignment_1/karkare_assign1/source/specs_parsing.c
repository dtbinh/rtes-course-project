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

	struct  period_task*	ptask 	=	NULL;			// To create the periodic task
	struct 	period_task*	ptmp	=	NULL;			// To hold the last position in the linked list
	struct	event_task*	etask	= 	NULL;			// to create the event task
	struct 	event_task*	etmp	=	NULL;			// To hold the last position in the linked list
	struct 	activities*	act	=	NULL;			// To create the activity
	
	int 	token_count = 1;
	int 	task_num;
	int 	i;
	size_t	n;
	
	char	token1[10];
	char	token2[10];

	
	// Creating the full path name
	strcpy(fullfilename,filepath);
	strcat(fullfilename,filename);


	// Opening the file for reading , if any problem exit the program
	fp = fopen((const char*)fullfilename , "r");
	if(!fp)
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

		// Extract first token
		data = strtok(readline," ");
		if(strcmp(data,"P") == 0)	 		// If first token is P then its periodic task
		{
			ptask = (struct period_task*)malloc(sizeof(struct period_task));
			ptask->start 	= NULL;
			ptask->currpos	= NULL;
			ptask->next	= NULL;

			// Adding the task to the periodic task linked list		
			if(task->phead == NULL)
			{
				task->phead = ptask;
				ptmp = ptask;
			}
			else
			{
				ptmp->next = ptask;
				ptmp = ptask;
			}

			// Extracting the period 
			data = strtok(NULL," ");
			ptask->period = atoi(data);

			// Extracting the priority
			data = strtok(NULL," ");
			ptask->priority = atoi(data);

			// Extracting the Body of the task
			while(data = strtok(NULL," "))
			{
				act = (struct activities*)malloc(sizeof(struct activities));
				act->next = NULL;
				if(data[0] >= '0' && data[0] <= '9')
					

			}
			

		}
		else						// If first token is A then its event task
		{
			etask = (struct event_task*)malloc(sizeof(struct event_task));
                        etask->start    = NULL;
                        etask->currpos  = NULL;
                        etask->next     = NULL;

                        // Adding the task to the event task linked list            
                        if(task->ehead == NULL)
                        {
                                task->ehead = etask;
                                etmp = etask;
                        }
                        else
                        {
                                etmp->next = etask;
                                etmp = etask;
                        }

			// Extracting the event
			data = strtok(NULL," ");
			etask->event = atoi(data);

			// Extracting the priority
			data = strtok(NULL," ");
			etask->priority = atoi(data);
		
		}
		

		do{
			if(data[strlen(data)-1] == '\n')
				data[strlen(data) -1] = '\0';
			printf("Token = %s \n",data);
			

			data = strtok(NULL, " ");
		}while(data);

	}



	// Deallocating the memory
	if(readline)
		free(readline);
	if(fullfilename)
		free(fullfilename);

	fclose(fp);
}
