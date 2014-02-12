#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <error.h>
#include <sched.h>
#include <time.h>
#include <signal.h>

#include "../include/structures.h"

pthread_mutex_t		mutexLock[10];			// Mutex locks
volatile int		condition_variable;		// Variable to let all the task know the time is over
struct event_list*	elist[10];			// contains the list of thread ids waiting for the event signal
pthread_barrier_t	activation;			// Activation barrier
pthread_barrier_t	completion;			// Completion barrier


// Main code starts here
int main(int argc,char** argv)
{
	char* filename;						// Stores the specification filename

	struct task_struct_t*	etmp	= NULL;				
	struct event_list*	tmp;
	struct task_list tasks;					// Main structure to store the task data


	int i;
	int err;						// Error Code
	pthread_t  tid;						// thread id

    	// Mutex and pthread attribute variables
	pthread_mutexattr_t 	lock_attr;
	pthread_attr_t		thread_attr;
	struct sched_param	thread_param;

	// timing structures
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
	

	// Parse the specification file
	parse_specs(&tasks,filename);



	// Initializing the condition_variable used to 
	condition_variable = 1;
	
	// Initializing the barriers
	pthread_barrier_init(&activation,NULL,tasks.num_task+2);		// +2 for main and event handling task
	pthread_barrier_init(&completion,NULL,tasks.num_task+2);


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
		}
		else if(etmp->task_type == 'A'){
			err  = pthread_create(&(etmp->tid),(const pthread_attr_t*)&thread_attr, (void *)event_task, (void*)etmp);
                        if(err){
                                printf("Error creating the threads \n");
                                printf("Error: %s \n",strerror(err));
                                exit(1);
                        }
		}

		etmp = etmp->next;

	}

	// Activating the tasks
	pthread_barrier_wait(&activation);
	printf("Task Activated \n");
	
	// Sleep the main thread for the total execution time
	sleep_time.tv_sec = (tasks.total_time / 1000);
        sleep_time.tv_nsec = (tasks.total_time %1000) * 1000000;
	nanosleep(&sleep_time,&time_rem);

	// Letting tasks know that time is up
	condition_variable = 0;
	
	// Waking up the event threads
	for(i = 0; i < 10;i++)
	{
		tmp = elist[i];
		while(tmp != NULL){
			pthread_kill(tmp->tid,SIGUSR1);
			tmp = tmp->next;
		}

	}	

	// Wait for all the threads to finish the tasks
	pthread_barrier_wait(&completion);
	printf("Task Completed \n");


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
