#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structures.h"


/*
 *  This functions checks if the total utilization of the task
 *  is less than 1 or not and perform other operation based on the 
 *  utilization value.
 */
void edf_calculate_utilization(struct task_set* tset)
{
	int  i;
	int  period_deadline = 0;
	float util = 0.0;

	struct TCB_t* tmp;

	// calculating the utilization
	tmp = tset->head;
	while(tmp != NULL){
		util = util + (tmp->wcet / min(tmp->deadline,tmp->period));
		tmp = tmp->next;
	}

	// If utilization is less than 1 then task set is schedulable
	if(util <= 1.0){
		printf("EDF : Task set is schedulable. U = %f \n",util);
		return;
	}
	
	// If utilizationis greater than 1 then task set may or may not be schedulable
	// depending on if the deadline equals period or not 

	// We check if period equals deadline or not
	period_deadline = common_deadline_period_relation(tset->head);

	// If period equals deadline , task set not schedulable
	if(period_deadline == 0){
		printf("EDF : Period = deadline . Task set is not schedulable since U = %f greater than 1 \n",util);
		return;
	}
	
	// If deadline is less than period , apply loading factor analysis
	printf("EDF: Period != deadline and utilization = %f . Loading Factor Analysis req !! \n",util);
	edf_loading_factor_analysis(tset->head);
	
}






/*
 *  This function checks the laoding factor of the cpu and 
 *  decides if the given task set is schedulable or not
 */
void edf_loading_factor_analysis(struct TCB_t* head)
{
	int	i = 0;
	int 	j = 0;
	int   num_points = 0;

	float  testingPoint;
	float  procDemand;
	float  loadFactor;
	float  L;		// busy_period	
	float* tpArray;

	struct TCB_t* 	tmp;

	// Calculating the busy period
	L = edf_synch_busy_period(head);
	if(isinf(L)){
		printf("EDF: Task set not schedulable. Busy Period infinity. \n");
		return;
	}

	// Calculating the testing points from 0 to L time
	// Finding number of testing points 
	tmp = head;
	while(tmp != NULL)
	{	
		i = 0;
		testingPoint = 0.0;
		while(testingPoint <= L){
			testingPoint = tmp->deadline + (i*tmp->period);
			i++;
			num_points++;
		}
		num_points--;
		tmp = tmp->next;
	}

	//Allocating testing point array
	tpArray = (float*)malloc(sizeof(float)*num_points);

	// Adding the testing points to the array
	j = 0;
	tmp = head;
        while(tmp != NULL)
        {
                i = 0;
                testingPoint = 0.0;
                while(testingPoint <= L){
                	testingPoint = tmp->deadline + (i*tmp->period);
			if(testingPoint <= L){
				tpArray[j] = testingPoint;
				j++;
			}
                        i++;
                }
                tmp = tmp->next;
        }

	// Calculating the loading factor at each testing point  in the array
	for(i = 0;i < num_points;i++)
	{
		tmp = head;
		procDemand = 0.0;
		loadFactor = 0.0;
		while(tmp != NULL){
			j = 0;
			testingPoint = 0.0;
			while(testingPoint <= tpArray[i]){
				testingPoint = tmp->deadline + (j*tmp->period);
				if(testingPoint <= tpArray[i]){
					procDemand = procDemand + tmp->wcet;
				}
				j++;
			}
			tmp = tmp->next;
		}
		loadFactor = procDemand / tpArray[i];

		// If loading Factor is greater than 1 for any instance then tasks are not schedulabel
		if(loadFactor > 1){
			printf("EDF: Task set not Schedulable. Failed Loading factor test \n");
			return;
		}
	}

	printf("EDF: Task set schedulable. All task passed loading factor test \n");

}


/*
 *  This function calculates the sync busy period 
 */
float edf_synch_busy_period(struct TCB_t* head)
{
	int i = 0;

	float busyPeriod1 = 0.0;
	float busyPeriod2 = 0.0;

	struct TCB_t* tmp;

	// Calculating the initial guess
	tmp = head;
	while(tmp != NULL){
		busyPeriod1 = busyPeriod1 + tmp->wcet;
		tmp = tmp->next;
	}


	// Calculating the guess iteratively
        do{
	        if(i != 0)
        	        busyPeriod1 = busyPeriod2;

		busyPeriod2 = 0.0;
                tmp = head;
                while(tmp != NULL){
                	busyPeriod2 = busyPeriod2 + (ceil(busyPeriod1/tmp->period)  *tmp->wcet );
                        tmp = tmp->next;
                }
                i++;
	}while(busyPeriod2 != busyPeriod1);

	if(isinf(busyPeriod2))
		printf("Not Schedulable\n");
	
	return busyPeriod2;

}




/*
 *  This function sorts and remove the duplicates from the 
 *  testing points array provided to it as argument
 */
void edf_sort_and_remove_dup(float** arr)
{
	



}
