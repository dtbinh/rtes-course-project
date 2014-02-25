#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__


struct TCB_t{
	int   		assignPriority;
	int   		currPriority;
	float 		wcet;
	float 		deadline;
	float 		period;
	struct TCB_t* 	next;
};

struct task_set{
	struct TCB_t*  	head;
	int		num_task;
	float		edf_util;
	float		edf_lf;
	float 		rm_util;
	float		rm_rt;
	float		dm_util;
	float		dm_rt;
//	float		fp_util;	
//	float		fp_rt;
};

extern inline float min(float, float );
extern inline float calculate_utilization(struct TCB_t* ,int); // if int arg is 1 then we use min{p,d} value else just use p value

void create_tcb_init(struct TCB_t** , int);
void destroy_tcb_init(struct TCB_t** , int);
int  common_deadline_period_relation(struct TCB_t*); 	// 0 - if equal , 1 - if d < p and 2 - if d > p


// Rate Monotonic function declarations
void  rm_assign_priority(struct TCB_t*);
void  rm_calculate_utilization(struct task_set*);
void  rm_response_time(struct TCB_t*,char*);
float rm_util(int);


// Deadline Monotonic function declarations
void  dm_assign_priority(struct TCB_t*);
void  dm_calculate_utilization(struct task_set*);


// Fixed priority scheduling function declarations
int fp_utilization_bound_test(struct TCB_t*,char*);
void fp_sort_task_by_assignPriority(struct TCB_t*);
void fixed_priority_analysis(struct task_set*);


// Earliest Deadline First (EDF) function declarations
void edf_calculate_utilization(struct task_set*);
void edf_loading_factor_analysis(struct TCB_t* );
void edf_sort_and_remove_dup(float** );
float edf_synch_busy_period(struct TCB_t*);



#endif	/* structures.h */
