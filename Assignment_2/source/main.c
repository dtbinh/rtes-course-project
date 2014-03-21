#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "structures.h"
#include "config.h"

int main(int argc,char** argv)
{
	#if MODE == 1
	int	numTaskSet = 0;
	int	i = 0;
	int 	num_task = 0;
	int	priority;
	
	int 	result;

	float 	wcet;
	float 	deadline;
	float 	period;

	struct TCB_t* 	tmp;
	#endif

	struct task_set	curr_task_set;
	curr_task_set.head = NULL;

	#if MODE == 1
	// Scanf for number of tasks in the set
	scanf("%d",&num_task);
	while(num_task)			// If the number of task is zero , exit the program
	{
		numTaskSet++;
	
		#if LOG_LVL != 0
			printf("Task set %d analysis \n",numTaskSet);
		#endif

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

		// Check the deadline perriod relation
		curr_task_set.period_deadline = common_deadline_period_relation(curr_task_set.head);

	#if LOG_LVL != 0
		if(curr_task_set.period_deadline)
			printf("Task set %d : Period != Deadline \n",numTaskSet);
		else
			printf("Task set %d : Period == Deadline \n",numTaskSet);
	#endif

		// Calculate the utilization both wiht min{p,d} and with just p
		curr_task_set.util_p = 	calculate_utilization(curr_task_set.head,0);
		curr_task_set.util_min_p_d = calculate_utilization(curr_task_set.head,1);	

		// rate monotonic analysis
		result = rm_analysis(&curr_task_set);

		// Deadline Monotonic analysis
		result = dm_analysis(&curr_task_set);

		// Fixed priority analysis
		result = fixed_priority_analysis(&curr_task_set);
		
		// EDF analysis
		result = edf_analysis(&curr_task_set);
	
	
					
		// Get the next task set,  number of tasks value
		scanf("%d",&num_task);
		destroy_tcb_init(&curr_task_set.head,num_task);

	#if LOG_LVL != 0
		printf("\n\n");
	#endif
		// to avoid the warning
		result++;
		
	}
	#else
		srand48(time(NULL));
		srand(time(NULL));
		printf("Wait for the analysis to be done !!\n");
		schedulability_analysis(&curr_task_set);
		printf("Analysis done , output in the ../test folder !! \n");
	#endif

	return 0;
}
