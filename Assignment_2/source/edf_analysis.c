#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structures.h"
#include "config.h"


struct node{
	int	testingPoint;
	struct node* next;
	struct node* prev;
};

void remove_dup_testingPoint(struct node**);

/*
 *  This functions checks if the total utilization of the task
 *  is less than 1 or not and perform other operation based on the 
 *  utilization value.
 */
int  edf_analysis(struct task_set* tset)
{
	int res = 0;

	float util = 0.0;

	// calculating the utilization
	util = tset->util_p;

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
	util = tset->util_min_p_d;


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

	// sort the task based on the their deadlines
	dm_assign_priority(tset->head);
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

	struct TCB_t* 	tmp;

	struct node*	new;
	struct node* 	tmp1;
	struct node* 	tpHead = NULL;
	

	// Calculating the busy period
	L = edf_synch_busy_period(head);
	if(isinf(L)){
	#if LOG_LVL != 0
		printf("EDF: Task set not schedulable. Busy Period infinity. \n");
	#endif
		return 0;
	}


	// Calculating the testing points from 0 to L time
	// and storing it in the list
	tmp = head;
	while(tmp != NULL)
	{	
		i = 0;
		testingPoint = 0.0;
		while(testingPoint <= L){
			new = (struct node*)malloc(sizeof(struct node));
			new->next = NULL;
			new->prev = NULL;
			testingPoint = tmp->deadline + (i*tmp->period);
			new->testingPoint = testingPoint;

			if(tpHead == NULL){
				tpHead = new;
				tmp1 = new;
			}
			else{
				tmp1->next = new;
				new->prev = tmp1;
				tmp1 = new;
			}
			
			i++;
			num_points++;
		}
		num_points--;
		tmp = tmp->next;
	}

	// Sorting and removing teh duplicate
//	remove_dup_testingPoint(&tpHead);
	

	// Calculating the loading factor at each testing point  in the array
	tmp1 = tpHead;
	while(tmp1 != NULL)
	{
		tmp = head;
		procDemand = 0.0;
		loadFactor = 0.0;
		while(tmp != NULL){
			j = 0;
			testingPoint = 0.0;
			while(testingPoint <= tmp1->testingPoint){
				testingPoint = tmp->deadline + (j*tmp->period);
				if(testingPoint <= tmp1->testingPoint){
					procDemand = procDemand + tmp->wcet;
				}
				j++;
			}
			tmp = tmp->next;
		}
		loadFactor = procDemand / tmp1->testingPoint;

		// If loading Factor is greater than 1 for any instance then tasks are not schedulabel
		if(loadFactor > 1){
		#if LOG_LVL != 0
			printf("EDF: Task set not Schedulable. Failed Loading factor test \n");
		#endif
			return 0;
		}
		tmp1 = tmp1->next;
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




/*
 *  This function sort the testing points and remove any duplicates.
 */
void remove_dup_testingPoint(struct node** head)
{
        struct node* tmp = NULL;
        struct node* rem = NULL;
        struct node* fmem = NULL;

        tmp = *head;

        while(tmp != NULL)
        {
                if(tmp->next == NULL)
                        break;
                rem = tmp->next;
                while(rem != NULL){
                        if(rem->testingPoint == tmp->testingPoint){
                                if(rem->next != NULL){
                                        rem->next->prev = rem->prev;
                                        rem->prev->next = rem->next;
                                        fmem = rem;
                                        rem = rem->prev;
                                }
                                else{
                                        rem->prev->next = rem->next;
                                        fmem = rem;
                                        rem = rem->prev;
                                }

                                if(fmem)
                                        free(fmem);
                        }
                        rem = rem->next;
                }
                tmp = tmp->next;

        }


}

