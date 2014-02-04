#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

/* 
 *  This struture contains the a single activity in the task body like
 *  computation loop size , locking or unlocking the specific mutex	
 */
struct activities{
		int job;			// Contains the iteration or mutex number
		int type;			// C if computation , L if lock mutex , U if unlock mutex
		struct activities* next;	// points to the next activity to do
	};


/*
 *  This structure contains the data of a periodic task such as
 *  period , priority and the activities to be done in the task.
 */
struct period_task{
		int period;			// Period of the periodic task
		int priority;			// RealTime priority of the task
		struct activities* start;	// Linklist head to store all the activity of a periodic task
		struct activities* currpos;	// Which current activity a task is performing
	};


/* 
 *  This structure contains the data of a periodic task such as
 *  on which event this task will run , priority and the activities to be done in the task.
 */
struct event_task{
		int event;			// This task is triggereb by this event number
		int priority;			// Realtime priority of the task
		struct activities* start;       // Linklist head to store all the activity of a event-driven task
                struct activities* currpos;     // Which current activity a task is performing
        };

/*
 *  This structure contains linked list of all the periodic and 
 *  event-driven tasks along with the total time of execution
 */
struct task_list{
		int total_time;			// total execution time of the program
		struct period_task* p_head;	// Linklist to store all the preiodic tasks data
		struct event_task*  e_head;	// Linklist to store all the event tasks data
	};


void periodic_function(void*);
void event_function(void*);

void parse_specs(struct task_list* , char*);

#endif	/* structures.h */
