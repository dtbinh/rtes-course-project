#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

/* 
 *  This struture contains the a single activity in the task body like
 *  computation loop size , locking or unlocking the specific mutex	
 */
struct activities{
		int work;			// Contains the iteration or mutex number
		int type;			// C if computation , L if lock mutex , U if unlock mutex
		struct activities* next;	// points to the next activity to do
	};


/*
 *  This structure contains the data of a  task such as
 *  period_event , priority and the activities to be done in the task.
 */
struct task_struct_t{
		pthread_t  tid;
		int task_type;			// 'P' for periodice task and 'A' for Aperiodic task
		int period_event;		// Period/Event of the task
		int priority;			// RealTime priority of the task
		struct activities* start;	// Linklist head to store all the activity of a periodic task
		struct activities* currpos;	// Which current activity a task is performing
		struct task_struct_t* next;
	};


/*
 *  This structure contains linked list of all the periodic and 
 *  event-driven tasks along with the total time of execution
 */
struct task_list{
		int total_time;			// total execution time of the program
		int num_task;			// Number of tasks 
		struct task_struct_t* head;	// Linklist to store all the tasks data
	};

/*
 *  This structure stores the list of pthread ids in form of linked list.
 *  Which is used to send the event signal to the registered thread.
 */ 
struct event_list {
        pthread_t tid;
        struct event_list* next;
};


void periodic_task(void*);
void event_function(void*);

void parse_specs(struct task_list* , char*);

void event_handler();
void register_for_event(pthread_t, int);

#endif	/* structures.h */
