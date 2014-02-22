#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__


struct TCB_t{
	int   assignPriority;
	int   currPriority;
	float wcet;
	float deadline;
	float period;
	struct TCB_t* next;
};

struct task_set{
	struct TCB_t*  	head;
	float		edf_util;
	float		edf_lf;
	float 		rm_util;
	float		rm_rt;
	float		dm_util;
	float		dm_rt;
//	float		fp_util;	
//	float		fp_rt;
};




void create_tcb_init(struct TCB_t** , int);
void destroy_tcb_init(struct TCB_t** , int);

#endif	/* structures.h */
