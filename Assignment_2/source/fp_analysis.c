#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "config.h"


/*
 *  This function does the fixed priority analysis on the given task set.
 */
int fixed_priority_analysis(struct task_set* tset)
{
	int 	res;

	float util = 0.0;
	struct TCB_t* tmp;

	//check if the utilization is less than 1
	tmp = tset->head;
	while(tmp != NULL){
		util = util + (tmp->wcet / tmp->period);
		tmp = tmp->next;
	}

	if(util > 1.0){
	#if LOG_LVL != 0
		printf("Fixed Priority : Task set not schedulable. U = %f > 1 \n",util);
	#endif
		return 0;
	}

	// sorting the task based on their assigned priority
	fp_sort_task_by_assignPriority(tset->head);
	
	// doing utilization bound test 
	res = fp_utilization_bound_test(tset->head,"Fixed Priority");

	// If utilization bount test failed then we do response time analysis
	if(res == 0){
		res = rm_response_time(tset->head,"Fixed Priority");
	}

	return res;
	
}



/*
 *  This function sorts the task in the order of the assigned priority.
 */
void fp_sort_task_by_assignPriority(struct TCB_t* head)
{

        int     tmp_ap;
        int     tmp_cp;
        float   tmp_wcet;
        float   tmp_dl;
        float   tmp_p;


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
                        if(tmp2->next->assignPriority < min->assignPriority){
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
                min->wcet           = tmp1->wcet;
                min->deadline       = tmp1->deadline;
                min->period         = tmp1->period;

                tmp1->assignPriority = tmp_ap;
                tmp1->currPriority   = tmp_cp;
                tmp1->wcet           = tmp_wcet;
                tmp1->deadline       = tmp_dl;
                tmp1->period         = tmp_p;

                tmp1 = tmp1->next;
        }

}




/*
 *  This function calculate the effective utilization of each 
 *  task and check if they meet the sufficient condition
 */
int fp_utilization_bound_test(struct TCB_t* head,char* aType)
{
	int count = 0;
	int taskCount = 0;

	float util = 0;

	struct TCB_t* tmp1;
	struct TCB_t* tmp2;

	// calculate effiective utilization for each task 
	tmp1 = head;
	while(tmp1 != NULL){
		taskCount++;
		tmp2 = head;
		util = 0.0;
		count = 0;
		while(tmp2  != tmp1){
			if(tmp2->period < tmp1->deadline){
				count++;
				util  = util + (tmp2->wcet/tmp2->period);
			}
			else{
				util += (tmp2->wcet/tmp1->period);
			}
			tmp2 = tmp2->next;
		}
		util += (tmp1->wcet/tmp1->period);
		count++;

		if(util > rm_util(count)){
		#if LOG_LVL != 0
			printf("%s : Task %d failed the utilization bount test. U = %f > %f (U(%d)) \n",aType,taskCount,util,rm_util(count),count);
			printf("%s : Need to apply Response Time analysis \n",aType);
		#endif
			return 0;
		}
		tmp1 = tmp1->next;
	}

	#if LOG_LVL != 0
	printf("%s : Task set passed Utilization bound test. Task set schedulable. \n",aType);
	#endif

	return 1;
}

