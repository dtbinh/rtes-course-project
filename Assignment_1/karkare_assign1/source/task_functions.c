#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "../include/structures.h"

extern pthread_mutex_t          mutexLock[10];
extern volatile int		condition_variable;
extern pthread_barrier_t	activation;
extern pthread_barrier_t	completion;

void timespec_diff(struct timespec* time1, struct timespec* time2,struct timespec* res)
{
	long tmp;

	if(time1->tv_sec < time2->tv_sec)
	{
		res->tv_sec = time2->tv_sec - time1->tv_sec - 1;
		tmp   = time2->tv_nsec + (999999999 - time1->tv_nsec);
		if(tmp > 999999999)
		{
			res->tv_nsec = tmp%1000000000;
			res->tv_sec++;
		}	
		else
			res->tv_nsec = tmp;

	}
	else
	{
		res->tv_sec = 0;
		res->tv_nsec = time2->tv_nsec - time1->tv_nsec;
	}


}

void periodic_task(void* data)
{
	struct task_struct_t* task; 
	struct timespec time1,time2,time3,rem,sleep_time;
	
	int loop_var	= 0;
	int flag = 0;
	long int time_msec = 0;

	task = (struct task_struct_t*)data;

	
	// Barrier Synchronization here
	pthread_barrier_wait(&activation);
	

	while( condition_variable )
	{
		flag = 0;
		clock_gettime(CLOCK_MONOTONIC ,&time1);	

		// Doing the Job
		task->currpos = task->start;
		while(task->currpos != NULL)
		{
			if(task->currpos->type == 'C')
  				for(loop_var = 0;loop_var < task->currpos->work;loop_var++);
			else if(task->currpos->type == 'L'){ 
				pthread_mutex_lock(&mutexLock[task->currpos->work] );
			}
			else{
				pthread_mutex_unlock(&mutexLock[task->currpos->work]);
			}

			task->currpos = task->currpos->next;
		}


		// Checking for the overrun
		clock_gettime(CLOCK_MONOTONIC,&time2);
		timespec_diff(&time1,&time2,&time3);
		time_msec = (time3.tv_sec * 1000 + time3.tv_nsec/1000000);

		if(time_msec  > task->period_event){
			flag = 1;
		}

		if(!flag)		// If not overrun then we have to sleep for remaining time
		{
			sleep_time.tv_sec = (task->period_event / 1000);
			sleep_time.tv_nsec = (task->period_event %1000) * 1000000;
			timespec_diff(&time3,&sleep_time,&rem);
			nanosleep(&rem,&time3);
		}

	}

	pthread_barrier_wait(&completion);
	printf("exit the thread \n");
}




void event_task(void* data)
{
	struct task_struct_t*  task;


	task = (struct task_struct_t*)data;

	// Register the thread to receive the event signal

	// Barrier synchronization here 

	while(condition_variable)
	{
		




	}

}
