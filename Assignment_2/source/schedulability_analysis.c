#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#include "structures.h"
#include "config.h"

#if MODE == 0

#define NUM_TASKSET	100


/*
 *  This function creates the filename based on the 
 *  argument provided. output_<taskset_size>_<deadline_policy>.txt
 */
void create_filename(char** filename,int taskset_size,int deadline_policy)
{
	char* pathname = "../test/output_";
	char* dp = (char*)malloc(sizeof(char)*10);
	char* end_filename = (char*)malloc(sizeof(char)*20);

	strcpy(*filename,pathname);

	if(deadline_policy == 0)
		strcpy(dp,"full");
	else
		strcpy(dp,"half");

	sprintf(end_filename, "%d_%s.txt",taskset_size,dp);
	
	strcat(*filename,end_filename);

	if(end_filename)
		free(end_filename);
	if(dp)
		free(dp);

}



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

	task_per_range = n/2;


	tmp = head;
	for(i = 0;i < n;i++){
		range = i/task_per_range;
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

	long long int tests = 0;
	
	float	curr_util;
	float	percent[3] = {0.0,0.0,0.0};
	float 	util_range[] = {0.05,0.15,0.25,0.35,0.45,0.55,0.65,0.75,0.85,0.95};

	char*   filename;

	FILE*	fp;	

	filename = (char*)malloc(sizeof(char)*100);


	// Starting the schedulability analysis
	for(i = 0; i < 3; i++){					// For taskset size
		curr_taskset_num = taskset_size[i];

		for(j = 0; j < 2; j++){				// For Deadline policy
			curr_deadline_policy = j;

			// Create the filename
			create_filename(&filename,curr_taskset_num,curr_deadline_policy);
			printf("File name = %s\n",filename);

			// Open the file to record the data
			fp = fopen(filename,"w");
			if(fp == NULL){
				printf("Error creating the data file ! Abort execution !! \n");
				exit(1);
			}	
					
			for(k = 0 ; k < 10 ;k++){		// For utilization
				curr_util = util_range[k];
				test_passed[0] = 0;test_passed[1] = 0;test_passed[2] = 0;
				percent[0] = 0.0;percent[1] = 0.0;percent[2] = 0.0;

				for(l = 0; l < NUM_TASKSET;l++){	// For averaging over NUM_TASKSET test	

					//Creating the taskset
					create_tcb_init(&tset->head,curr_taskset_num);
					tset->num_task = curr_taskset_num;
					uUniFast(curr_taskset_num,(double)curr_util,tset->head);
					genTaskPeriod(curr_taskset_num,tset->head);
					genTaskDeadline(curr_taskset_num,tset->head,curr_deadline_policy);

					// checking the deadline period relationship
					tset->period_deadline = common_deadline_period_relation(tset->head);
			
					 // Calculate the utilization both wiht min{p,d} and with just p
			                tset->util_p =  calculate_utilization(tset->head,0);
				        tset->util_min_p_d = calculate_utilization(tset->head,1);


					// Analysing the taskset with EDF , RM and DM
					test_passed[0] += edf_analysis(tset);
					test_passed[1] += rm_analysis(tset);
					test_passed[2] += dm_analysis(tset);			
				

					tests++;	
				}
				
			
				// Calculate the percentage of task passed the test and store it 
				percent[0] =  ((float)test_passed[0] / (float)NUM_TASKSET) * 100.0;
				percent[1] =  ((float)test_passed[1] / (float)NUM_TASKSET) * 100.0;
				percent[2] =  ((float)test_passed[2] / (float)NUM_TASKSET) * 100.0;

				fprintf(fp,"%f %f %f\n",percent[0],percent[1],percent[2]);

			}
			// Close the file 
			fclose(fp);
		}
		// Delete the task head
		destroy_tcb_init(&tset->head,curr_taskset_num);

	}


	// Dellocating the memory
	destroy_tcb_init(&tset->head,0);		

}




#endif
