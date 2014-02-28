#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__


struct TCB_t{
	#if MODE == 0
	double 		util;
	#endif
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
	int		period_deadline;
};

extern inline float min(float, float );
extern inline float calculate_utilization(struct TCB_t* ,int); // if int arg is 1 then we use min{p,d} value else just use p value

void  create_tcb_init(struct TCB_t** , int);
void  destroy_tcb_init(struct TCB_t** , int);
int   common_deadline_period_relation(struct TCB_t*); 	// 0 - if equal , 1 - if d < p and 2 - if d > p


// Rate Monotonic function declarations
void  rm_assign_priority(struct TCB_t*);
int   rm_analysis(struct task_set*);
int   rm_response_time(struct TCB_t*,char*);
float rm_util(int);


// Deadline Monotonic function declarations
void  dm_assign_priority(struct TCB_t*);
int   dm_analysis(struct task_set*);


// Fixed priority scheduling function declarations
int   fp_utilization_bound_test(struct TCB_t*,char*);
void  fp_sort_task_by_assignPriority(struct TCB_t*);
int   fixed_priority_analysis(struct task_set*);


// Earliest Deadline First (EDF) function declarations
int   edf_analysis(struct task_set*);
int   edf_loading_factor_analysis(struct TCB_t* );
float edf_synch_busy_period(struct TCB_t*);

#if MODE == 0
// Schedulbility analysis function declarations
void genTaskDeadline(int,struct TCB_t*, int);
void genTaskPeriod(int,struct TCB_t*);
void uUniFast(int,double,struct TCB_t* );
void schedulability_analysis(struct task_set*);
void create_filename(char**,int,int);
#endif




#endif	/* structures.h */
