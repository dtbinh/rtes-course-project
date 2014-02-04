#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "../include/structures.h"


int main(int argc,char** argv)
{
	char* filename;
	struct period_task*	ptmp	= NULL;
	struct event_task*	etmp	= NULL;
	struct activities*	atmp 	= NULL;
	struct task_list tasks;

	tasks.phead = NULL;
	tasks.ehead = NULL;	

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


	// Printing the task specs
	ptmp = tasks.phead;
	etmp = tasks.ehead;
	
	printf("Total time of execution = %d \n",tasks.total_time);

	printf("Periodic tasks \n");
	while(ptmp !=  NULL)
	{
		printf("%d -- %d --- \t",ptmp->period,ptmp->priority);
		atmp = ptmp->start;
		while(atmp != NULL){
			printf("%d-%d    ",atmp->type,atmp->work);
			atmp = atmp->next;
		}
		printf("\n");
		ptmp = ptmp->next;
	}

	printf("Aperiodice Tasks \n");
	while(etmp !=  NULL)
        {
                printf("%d -- %d --- \t",etmp->event,etmp->priority);
                atmp = etmp->start;
                while(atmp != NULL){
                        printf("%d-%d    ",atmp->type,atmp->work);
                        atmp = atmp->next;
                }
                printf("\n");
                etmp = etmp->next;
        }



	if(!filename)
		free(filename);

	return 0;
}
