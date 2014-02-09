#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <error.h>
#include <sched.h>
#include <time.h>

#include "../include/structures.h"

pthread_mutex_t		mutexLock[10];
volatile int		condition_variable;
struct event_list*	elist[10];
pthread_barrier_t	activation;
pthread_barrier_t	completion;


int main(int argc,char** argv)
{
	char* filename;						// Stores the specification filename
	struct task_struct_t*	etmp	= NULL;				
	struct activities*	atmp 	= NULL;
	struct event_list*	tmp;
	struct task_list tasks;


	int i;
	int err;
	pthread_t  tid;

    	// Mutex and pthread attribute variables
	pthread_mutexattr_t 	lock_attr;
	pthread_attr_t		thread_attr;
	struct sched_param	thread_param;

	struct timespec		sleep_time;
	struct timespec		time_rem;

	// Initializing the variables
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


	// Storing the commandline argument in the variable
	filename = (char*)malloc(sizeof(char)*30);
	strcpy(filename,argv[1]);
	printf("Filename = %s \n",filename);
	

	// Parse the specification file
	parse_specs(&tasks,filename);


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

	// Regestering for the events
	register_for_event(10,3);
	register_for_event(12,3);


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


	condition_variable = 1;
	
	// Initializing the barriers
	pthread_barrier_init(&activation,NULL,2);
	pthread_barrier_init(&completion,NULL,2);

	// Setting up the mutexes attribute and initializing the mutex
	pthread_mutexattr_init(&lock_attr);
	pthread_mutexattr_setprotocol(&lock_attr, PTHREAD_PRIO_INHERIT);
	for(i = 0;i < 10;i++)
		pthread_mutex_init(&mutexLock[i],&lock_attr);

	// Setting up the thead attribute
	pthread_attr_init(&thread_attr);
	pthread_attr_setschedpolicy(&thread_attr,SCHED_FIFO);

	// Creating the event handling thread
	thread_param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	pthread_attr_setschedparam(&thread_attr,&thread_param);
	err = pthread_create(&tid, (const pthread_attr_t*)&thread_attr, (void*) event_handler,NULL);
	if(err){
	        printf("Error creating the threads \n");
                printf("Error: %s \n",strerror(err));
                exit(1);
        }


	// Creating the task threads
	etmp = tasks.head;
	while(etmp != NULL)
	{
		// Setting the priority of the thread 
		thread_param.sched_priority = etmp->priority;	
		pthread_attr_setschedparam(&thread_attr,&thread_param);

		// Create the thread
		if(etmp->task_type == 'P'){
			err = pthread_create(&(etmp->tid),(const pthread_attr_t*)&thread_attr, (void *)periodic_task, (void*)etmp);
			if(err){
				printf("Error creating the threads \n");
				printf("Error: %s \n",strerror(err));
				exit(1);
			}
			printf("Thread id = %d \n",(int)etmp->tid);
		}

		etmp = etmp->next;

	}

	// Barrier synchronization here
	pthread_barrier_wait(&activation);
	
	// Sleep the main thread for the toal execution time
	sleep_time.tv_sec = (tasks.total_time / 1000);
        sleep_time.tv_nsec = (tasks.total_time %1000) * 1000000;
	printf("main thread sleep %d -- %ld \n",(int)sleep_time.tv_sec,sleep_time.tv_nsec);
	nanosleep(&sleep_time,&time_rem);

	condition_variable = 0;

	printf("main thread wakes \n");
	pthread_barrier_wait(&completion);

 	// Wait for all the threads to exit
//	etmp = tasks.head;
//	while(etmp != NULL)
//	{
//		if( etmp->tid != -1)
//			pthread_join(etmp->tid,NULL);
//		
//	}

	printf("Pthread barrier done \n");

	// Destroying the mutex
	for(i = 0;i < 10;i++)
		pthread_mutex_destroy(&mutexLock[i]);

	// Destroying the mutex attrib
	pthread_mutexattr_destroy(&lock_attr);

	// Destroying the thread attribute
	pthread_attr_destroy(&thread_attr);

	// Destroy the barriers
	pthread_barrier_destroy(&activation);
	pthread_barrier_destroy(&completion);	


	// Freeing the allocated memory
	if(filename)
		free(filename);

	return 0;
}
