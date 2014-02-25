#ifndef __config_H__
#define __config_H__


/*
 *  LOG_LVL defines how much log you want to see.
 *  0   -----	 no log at all , it is used if you wanna use the code for MODE 0 (defined below)
 *  1   ----- 	 minimal log is printed which is essential for MODE 1 (defined below)
 *  2   -----    This level prints each and every step in the execution ( used just for DEBUG MODE)
 */
#define  LOG_LVL	1


/*
 *  MODE  defines the execution mode of the program
 *  0    -----    In this mode automantic task details are generated and used to calculate the 
 *		  schedulability with different scheduling algos like DM , RM , Fixed Priority and EDF
 *		  and the result is stored in 4 different files in the order of the task generated
 *		  (NOTE: use LOG_LVL  0  to have silent operation)
 *
 *  1    -----	  In this mode, the program accepts the detail of the task from the standard input 
 *		  and applies DM , RM , fixed priority and EDF scheduling algo to find if they are
 *		  are schedulable or not. It prints the progress of the scheduling algos on the screen.
 *		  (NOTE: use LOG_LVL  1  to have best result. use of LOG_LVL not advised except for you need to debug the code)
 */
#define	 MODE		1





#endif  /* config.h */
