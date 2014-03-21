#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "structures.h"
#include "config.h"


/*
 *  This function assigns the priority to the task based on their deadline
 *  and sort them in ascending order
 */	
void dm_assign_priority(struct TCB_t* head)
{
	int 	i   = 0;

	int 	tmp_ap;	
	int 	tmp_cp;
	float 	tmp_wcet;
	float	tmp_dl;
	float 	tmp_p;
	

	struct TCB_t* min  = NULL;
	struct TCB_t* tmp1 = head;
	struct TCB_t* tmp2 = head;


	// sorting the linklist
	while(tmp1 != NULL)
	{
		min   = tmp1;
		tmp2  = tmp1;
		while(tmp2->next != NULL)
		{
			if(tmp2->next->deadline < min->deadline){
				min  = tmp2->next;
			}
			tmp2 = tmp2->next;

		}
		
		//Swap the data
		tmp_ap = min->assignPriority;
		tmp_cp = min->currPriority;
		tmp_wcet = min->wcet;
		tmp_dl = min->deadline;
		tmp_p  = min->period;

		min->assignPriority = tmp1->assignPriority;
		min->currPriority   = tmp1->currPriority;
		min->wcet	    = tmp1->wcet;
		min->deadline	    = tmp1->deadline;
		min->period	    = tmp1->period;

		tmp1->assignPriority = tmp_ap;
		tmp1->currPriority   = tmp_cp;
		tmp1->wcet	     = tmp_wcet;
		tmp1->deadline	     = tmp_dl;
		tmp1->period	     = tmp_p;

		tmp1 = tmp1->next;
	}

	// Giving them the current Priority
	i = 1;
	tmp1 = head;
	while(tmp1 != NULL){
		tmp1->currPriority = i;
		tmp1 = tmp1->next;
		i++;
	}	
}

/*
 *  This function calculates the utilization of the tasks and 
 *  checks if it satisfies the sufficent condition else calls 
 *  response time analysis to see if the tasks are schedulable.
 */
int  dm_analysis(struct task_set* tset)
{
	int	res = 1;

	float 	util = 0.0;	



	// Assign the priority to the task based on their period
	dm_assign_priority(tset->head);


	// Calculate utilization
	util = tset->util_p;

	// If utilization greater than 1 then not schedulable
	if(util > 1.0){
	#if LOG_LVL != 0
		printf("Deadline Monotonic: Task set not schedulable : U = %f greater than 1\n",util);
	#endif
		return 0;
	}
	

	// if deadline equals period then deadline monotonic is same as rate monotonic 
	if(tset->period_deadline == 0){
		if(util <= rm_util(tset->num_task)){
		#if LOG_LVL != 0
			printf("Deadline Monotonic : Schedulable :  U = %f < %f (U(%d)) \n",util,rm_util(tset->num_task),tset->num_task);
		#endif
		}
		else{
		#if LOG_LVL != 0
			printf("Deadline Monotonic : U = %f > %f (U(%d))  : RT Analysis required \n",util,rm_util(tset->num_task),tset->num_task);
		#endif
			res = rm_response_time(tset->head,"Deadline Monotonic");
		}
	} // If deadline not equals period then we need to do Response Time analysis 
	else{
		// Calculating new utilization
		util = tset->util_min_p_d;
		if(util <= rm_util(tset->num_task)){
		#if LOG_LVL != 0
			printf("Deadline Monotonic : new utilization = %f < %f (U(%d)) : Task set schedulable \n",util,rm_util(tset->num_task),tset->num_task);
		#endif
		}
		else{
		#if LOG_LVL != 0
			printf("Deadline Monotonic :  U = %f : RT Analysis required \n",util);
		#endif
			res = rm_response_time(tset->head,"Deadline Monotonic");
		}
	}

	return res;
}
