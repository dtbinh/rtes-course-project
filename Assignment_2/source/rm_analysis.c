#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structures.h"
#include "config.h"


inline float min(float num1, float num2){
	return num1 < num2 ? num1: num2;
}


/*
 *  This function calculate the utilization for the given task list
 *  If the type arg is 1 then it uses min{p,d} to calculate utilization
 *  If the type arg is 0 then it uses just p to calculate utilization
 */
inline float calculate_utilization(struct TCB_t* head, int type)
{
	float util = 0.0;
	float divider = 0.0;

	struct TCB_t* tmp;

	tmp = head;
	while(tmp != NULL){
		divider = tmp->period;
		if(type)
			divider = min(tmp->period,tmp->deadline);
		util = util + (tmp->wcet / divider);
		tmp = tmp->next;
	}
	

	return util;

}


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
 *  and sort them in ascending order
 */	
void rm_assign_priority(struct TCB_t* head)
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
			if(tmp2->next->period < min->period){
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
int  rm_analysis(struct task_set* tset)
{
	int 	res = 1;
	
	float 	util = 0.0;	



	// Assign the priority to the task based on their period
	rm_assign_priority(tset->head);


	// Calculate utilization
	util = calculate_utilization(tset->head,0);

	// If utilization greater than 1 then not schedulable
	if(util > 1.0){
	#if LOG_LVL != 0
		printf("Rate Monotonic: Task set not schedulable : U = %f greater than 1\n",util);
	#endif
		return 0;
	}
	

	// If utilization satisfies the nessary condition 
	// then we are done and the tasks are schedulable
	if(tset->period_deadline == 0){
		if(util <= rm_util(tset->num_task)){
		#if LOG_LVL != 0
			printf("Rate Monotonic : Schedulable  U = %f \n",util);
		#endif
		}
		else{
		#if LOG_LVL != 0
			printf("Rate Monotonic : U = %f > %f (U(%d))  : RT Analysis required \n",util,rm_util(tset->num_task),tset->num_task);
		#endif
			res = rm_response_time(tset->head,"Rate Monotonic");
		}
	}
	else{
		util = calculate_utilization(tset->head,1);
		if(util <= rm_util(tset->num_task)){
		#if LOG_LVL != 0
			printf("Rate Monotonic : new utilization = %f < %f (U(%d)) : Task set schedulable \n",util,rm_util(tset->num_task),tset->num_task);
		#endif
		}
		else{
		#if LOG_LVL != 0
			printf("Rate Monotonic :  U = %f : RT Analysis required \n",util);
		#endif
			res = rm_response_time(tset->head,"Rate Monotonic");
		}
	}

	return res;

}


/*
 *  This function checks whether deadline is equals period or less 
 */ 
int common_deadline_period_relation(struct TCB_t* head)
{
	int result = 0;
	struct TCB_t* tmp;

	tmp = head;

	while(tmp != NULL){
		if(tmp->deadline < tmp->period)
			result = 1;
		tmp = tmp->next;
	}


	return result;


}


/*
 *  This functions does the response time analysis and
 *  determines if the given tasks are schedulable or not
 */ 
int  rm_response_time(struct TCB_t* head, char* aType)
{
	int i = 1;
	float swap_tmp;
	float tmp_util= 0.0;
	float rTime1 = 0.0;
	float rTime2 = 0.0;

	struct TCB_t* tmp;	
	struct TCB_t* tmp1;
	

	tmp = head;

	// finding the first task in priority order which fails the utilization bound test
	if(strcmp(aType,"Fixed Priority") != 0){
	while(tmp != NULL){
		tmp_util = tmp_util + (tmp->wcet/min(tmp->period,tmp->deadline));
		if(tmp_util > rm_util(i)){
		#if LOG_LVL != 0
			printf("%s : Utilization of first %d task = %f > %f (U(%d)). Not OK. RT analyisis for task %d onward needed. \n",aType,i,tmp_util,rm_util(i),i,i);
		#endif
			break;
		}
		tmp = tmp->next;
		i++;
	}

	if(tmp == NULL){
	#if LOG_LVL != 0
		printf("%s : UB Analysis : All task meet their utilization bound. Schedulable \n",aType);
	#endif
		return 1;
	}

	}

	// Doing RT analysis on the task from i onwards
	while(tmp != NULL)
	{
		rTime1 = 0.0;
		rTime2 = 0.0;
		// find inital guess
		tmp1 = head;
		while(tmp1 != tmp){
			rTime1 = rTime1 + tmp1->wcet;	
			tmp1= tmp1->next;
		}
		rTime1 = rTime1 + tmp->wcet;
			

		// Iterate till you have same value in rTime1 and rTime2
		while(rTime2 != rTime1 && rTime1 <= tmp->deadline)
		{
			rTime2 = 0.0;
			tmp1 = head;
			while(tmp1 != tmp){
				rTime2 = rTime2 + (ceil(rTime1/tmp1->period)  *tmp1->wcet );
				tmp1 = tmp1->next;
			}
			rTime2 = rTime2 + tmp->wcet;

			//swap rTime1 and rTime2
			swap_tmp = rTime1;
			rTime1 = rTime2;
			rTime2 = swap_tmp;
		}

		if(rTime2 != rTime1){
		#if LOG_LVL != 0
			printf("%s : Task %d failed the response test. Intermediate response time  = %f ,  deadline = %f \n",aType,i,rTime1,tmp->deadline);
			printf("%s : Not Schedulable \n",aType);
		#endif
			return 0;
		}
		
		tmp = tmp->next;
		i++;

	}

	#if LOG_LVL != 0
	printf("%s : Task set is schedulable \n",aType);
	#endif

	return 1;


} 
