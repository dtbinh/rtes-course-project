#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "structures.h"

/* 
 *  This function calculates the sufficient condition upper bound 
 *  on a given number of tasks
 */
float rm_util(int num)
{
	float util = 0.0;
	float p	 = 1.0/num;	
	
	util = num * ( (powf(2,p))  - 1.0) ;

	return util;
}


/*
 *  This function assigns the priority to the task based on their period
 */	
void rm_assign_priority(struct TCB_t* head)
{
	int	len = 0;
	int 	i   = 0;
	int	j   = 0;
	int	pos = 0;

	float 	min = 0.0;
	float 	temp = 0;

	int*	position;
	int*	pri;
	float*	periods;
	
	struct TCB_t* tmp;

	// Finding number of tasks
	tmp = head;
	while(tmp != NULL){
		len++;
		tmp = tmp->next;
	}

	periods  = (float*)malloc(sizeof(float)*len);
	position = (int*)malloc(sizeof(int)*len);
	pri	 = (int*)malloc(sizeof(int)*len);

	//Getting the data from the tasks
	tmp = head;
	i = 0;
	while(tmp != NULL){
		periods[i] = tmp->period;
		position[i] = i;
		tmp = tmp->next;
		i++;
	}

	
	// sorting the periods array
	for(i = 0 ;i < len;i++){
		min = periods[i];
		pos = i;		
		for(j = i;j < len ;j++){
			if(periods[j] < min){
				min = periods[j];
				pos = j;
			}
		}
		
		// Swapping the min number and ith number in the array
		temp = periods[i];
		periods[i] = periods[pos];
		periods[pos] = temp;

		// Swapping the position array too
		temp = position[i];
		position[i] =  position[pos];
		position[pos] =  temp;
	}

	// Inverse the position array 
	for(i = 0;i < len;i++)	{
		pri[position[i]] = i + 1;
	}

	// Store the priority in the TCB
	tmp = head;
	i = 0;
	while(tmp != NULL)
	{
		tmp->currPriority = pri[i];
		tmp = tmp->next;
		i++;
	}

	if(periods)
		free(periods);
	if(position)
		free(position);
	if(pri)
		free(pri);
}




/*
 *  This function calculates the utilization of the tasks and 
 *  checks if it satisfies the sufficent condition else calls 
 *  response time analysis to see if the tasks are schedulable.
 */
void rm_calculate_utilization(struct task_set* tset)
{
	int 	period_deadline = 0;		// if 0 - equal , 1 - period > deadline , 2 - period < deadline
	float 	util = 0.0;	


	struct TCB_t* tmp;

	// Find the deadline period relation
 	

	// Calculate utilization
	tmp = tset->head;
	while(tmp != NULL)
	{
		util = util + (tmp->wcet / tmp->period);
		tmp = tmp->next;
	}

	// If utilization satisfies the nessary condition 
	// then we are done and the tasks are schedulable
	if(period_deadline == 0){
		if(util < rm_util(tset->num_task))
			printf("Rate Monotonic : Schedulable  U = %f \n",util);
		else{
			printf("Rate Monotonic : U = %f  : RT Analysis required \n",util);
			rm_response_time(tset->head);
		}
	}
	else if(period_deadline == 1)


}
