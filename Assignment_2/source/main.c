#include <stdio.h>
#include <unistd.h>

#include "structures.h"

int main(int argc,char** argv)
{
	int	numTaskSet = 0;
	int	i = 0;
	int 	num_task = 0;
	int	priority;

	float 	wcet;
	float 	deadline;
	float 	period;

	struct task_set	curr_task_set;
	struct TCB_t*	tmp;
	
	curr_task_set.head = NULL;


	// Scanf for number of tasks in the set
	scanf("%d",&num_task);
	while(num_task)			// If the number of task is zero , exit the program
	{
		numTaskSet++;
		printf("Task set %d analysis \n",numTaskSet);
		create_tcb_init(&curr_task_set.head,num_task);
		tmp = curr_task_set.head;

		curr_task_set.num_task = num_task;

		// Read the assigned priority for the tasks
		for(i = 0; i < num_task ;i++){
			scanf("%d",&priority);
			tmp->assignPriority = priority;
			tmp = tmp->next;
		}


		// Reading the task specification 
		tmp = curr_task_set.head;
		for(i = 0; i < num_task; i++){
			scanf("%f %f %f",&wcet,&deadline,&period);
			tmp->wcet = wcet;
			tmp->deadline = deadline;
			tmp->period = period;
			tmp = tmp->next;
		}

		// check if the utilization is less than 1 only then the scheduling matters

		// rate monotonic analysis
		rm_calculate_utilization(&curr_task_set);

		// Deadline Monotonic analysis
		dm_calculate_utilization(&curr_task_set);

		// Fixed priority analysis
		fixed_priority_analysis(&curr_task_set);
		
		// EDF analysis
		edf_calculate_utilization(&curr_task_set);
	
	
		// do the analysis on the given task set
					
		// Get the next task set,  number of tasks value
		scanf("%d",&num_task);
			
		destroy_tcb_init(&curr_task_set.head,num_task);

		printf("\n\n");
		sleep(1);
		
	}
	

	return 0;
}
