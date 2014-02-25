#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structures.h"
#include "config.h"

/*
 *  This functions checks if the total utilization of the task
 *  is less than 1 or not and perform other operation based on the 
 *  utilization value.
 */
int  edf_analysis(struct task_set* tset)
{
	int res = 0;

	float util = 0.0;

	struct TCB_t* tmp;

	// calculating the utilization
	tmp = tset->head;
	while(tmp != NULL){
		util = util + (tmp->wcet /tmp->period);
		tmp = tmp->next;
	}

	// If period equals deadline
	if(tset->period_deadline == 0){
		if(util > 1.0){
		#if LOG_LVL != 0
			printf("EDF : Task set is not schedulable since U = %f greater than 1 \n",util);
		#endif
			return 0;
		}
		else{
		#if LOG_LVL != 0
			printf("EDF : Task set is schedulable. U = %f \n",util);
		#endif
			return 1;
		}
	}

	
	// calculating the new utilization
	tmp = tset->head;
	util = 0.0;
	while(tmp != NULL){
		util = util + (tmp->wcet /min(tmp->deadline,tmp->period));
		tmp = tmp->next;
	}


	// If new utilization is less than 1 then set is schedulable
	if(util <= 1.0){
	#if LOG_LVL != 0
		printf("EDF: Task set is schedulable. eff. U = %f \n",util);
	#endif
		return 1;
	}

	// If new utilization is greater than 1 then task set may or may not be schedulable
	// Apply loading factor analysis
	#if LOG_LVL != 0
	printf("EDF: Utilization = %f . Loading Factor Analysis req !! \n",util);
	#endif

	res = edf_loading_factor_analysis(tset->head);

	return res;
	
}






/*
 *  This function checks the laoding factor of the cpu and 
 *  decides if the given task set is schedulable or not
 */
int  edf_loading_factor_analysis(struct TCB_t* head)
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
	#if LOG_LVL != 0
		printf("EDF: Task set not schedulable. Busy Period infinity. \n");
	#endif
		return 0;
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
		#if LOG_LVL != 0
			printf("EDF: Task set not Schedulable. Failed Loading factor test \n");
		#endif
			return 0;
		}
	}

	#if LOG_LVL != 0
	printf("EDF: Task set schedulable. All task passed loading factor test \n");
	#endif

	return 1;

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

	return busyPeriod2;

}
