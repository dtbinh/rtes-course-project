#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#include "structures.h"
#include "config.h"

#if MODE == 0


/*
 *  This function implements uunitfast algorithm to 
 *  calculate the utilization for the task set 
 */
void uUniFast(int n, double max_util,struct TCB_t* head)
{
	int i = 0;
        double nextSum;
        double tmp1 , tmp2;
        double sumU = max_util;

	struct TCB_t* tmp;

	tmp = head;
        for(i = 0; i < n-1 ;i++){
                tmp1 = drand48();
                tmp2 = (double)(n-i);
                nextSum = sumU * powf(tmp1,(1.0/tmp2));
		tmp->util = sumU - nextSum;
                sumU = nextSum;

		tmp = tmp->next;
        }
        tmp->util = sumU;
        return;
}



/*
 *  This function allocate the period to the task of the given taskset 
 *  from 2 different period range (1-1000,1000-10000)
 *  Alos it calculates the wcet based on the utilization and period
 */
void genTaskPeriod(int n,struct TCB_t* head)
{
	int i  = 0;
	int task_per_range = 0;
	int period;
	int range = 0;

	int range_start[] = {1,1000};
	int range_end[] = {1000,10000};
	struct TCB_t* tmp;

	task_per_range = n/5;


	tmp = head;
	for(i = 0;i < n;i++){
		range = n/task_per_range;
		period = (rand()%(range_end[range] - range_start[range])) + range_start[range];
		tmp->period = (float)period;
		tmp->wcet   = tmp->period * tmp->util;
		tmp = tmp->next;
	}

	
}



/*
 *  This function allocates the deadline to the tasks of the given taskset
 *  from 2 different methods based on the argument to the function
 *   If last arg is 0 - wcet to period is considered for deadline
 *   if last arg is 1 - from half way bewteen wcet and period to period is considered 
 */
void genTaskDeadline(int n, struct TCB_t* head, int type)
{
	float rand_deadline;
	struct TCB_t* tmp;

	tmp = head;
	while(tmp != NULL){
		rand_deadline = drand48();

		if(type == 0){
			tmp->deadline = tmp->wcet + ((tmp->period - tmp->wcet)*rand_deadline);
		}
		else{
			tmp->deadline = (tmp->wcet + (tmp->period - tmp->wcet)/2) + (((tmp->period-tmp->wcet)/2 - tmp->wcet)*rand_deadline);
		}

		tmp = tmp->next;
	}


}



/*
 *  This function generates the synthetic task set for 
 *  schedulability analysis of EDF,RM and DM
 */
void schedulability_analysis(struct task_set* tset)
{
	int	taskset_size[] = {10,20,50};
	int	test_passed[] = {0,0,0};
	int	curr_taskset_num;
	int	curr_deadline_policy;

	int 	i,j,k,l;
	
	char*   filepath = "../test/";
	char*   filename;
	


	struct 	TCB_t* tmp;

	for(i = 0; i < 3; i++){					// For taskset size
		curr_taskset_num = taskset_size[i];
		for(j = 0; j < 2; j++){				// For Deadline policy
			curr_deadline_policy = j;

		}

	}

	create_tcb_init(&tset->head,10);	
	tset->num_task = 10;
	
	uUniFast(10,0.5,tset->head);
	genTaskPeriod(10,tset->head);
	genTaskDeadline(10,tset->head,0);

	// Print the tasks
	tmp = tset->head;
	while(tmp != NULL){	
		printf("%f -- %f -- %f -- %f \n",tmp->util,tmp->wcet , tmp->deadline,tmp->period);
		tmp = tmp->next;
	}
		
}




#endif
