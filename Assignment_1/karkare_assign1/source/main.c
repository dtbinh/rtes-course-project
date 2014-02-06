#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "../include/structures.h"


int main(int argc,char** argv)
{
	char* filename;
	struct task_struct_t*	etmp	= NULL;
	struct activities*	atmp 	= NULL;
	struct event_list*	elist[10];
	struct event_list*	tmp;
	struct task_list tasks;

	int  i;

	tasks.head = NULL;

	for(i = 0;i < 10;i++)
		elist[i] = NULL;	

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

	printf("here \n");

	// Printing the task specs
	etmp = tasks.head;
	
	printf("Total time of execution = %d \n",tasks.total_time);

	printf("All Tasks \n");
	while(etmp !=  NULL)
        {
                printf("%c -- %d -- %d --- \t",etmp->task_type,etmp->period_event,etmp->priority);
                atmp = etmp->start;
                while(atmp != NULL){
                        printf("%d-%d    ",atmp->type,atmp->work);
                        atmp = atmp->next;
                }
                printf("\n");
                etmp = etmp->next;
        }

	register_for_event(10,3,elist);
	register_for_event(12,3,elist);

	for(i = 0; i < 10;i++)
	{
		tmp = elist[i];
		printf("%d -- ",i);
		while(tmp != NULL)
		{
			printf("%d \t",(int)tmp->tid);
			tmp = tmp->next;
		}
		printf("\n");

	}

	event_handler();


	if(!filename)
		free(filename);

	return 0;
}
