#include <stdio.h>
#include <unistd.h>

#include "structures.h"
#include "config.h"

int main(int argc,char** argv)
{
	int	numTaskSet = 0;
	int	i = 0;
	int 	num_task = 0;
	int	priority;
	
	int 	rm_result;
	int	dm_result;
	int	fp_result;
	int 	edf_result;

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


		// rate monotonic analysis
		rm_result = rm_analysis(&curr_task_set);

		// Deadline Monotonic analysis
		dm_result = dm_analysis(&curr_task_set);

		// Fixed priority analysis
		fp_result = fixed_priority_analysis(&curr_task_set);
		
		// EDF analysis
		edf_result = edf_analysis(&curr_task_set);
	
	
					
		// Get the next task set,  number of tasks value
		scanf("%d",&num_task);
		destroy_tcb_init(&curr_task_set.head,num_task);

	#if LOG_LVL != 0
		printf("\n\n");
	#endif
		sleep(1);
		
	}
	

	return 0;
}
