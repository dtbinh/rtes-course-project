#include <stdio.h>
#include <stdlib.h>

#include "structures.h"


/*
 *  This function creates the link list of TCB of 
 *  num provided as argument. It then initializes the 
 *  structures.
 */
void create_tcb_init(struct TCB_t** head, int num)
{
	int i;
	int pre_alloc_num = 0;

	struct TCB_t* new = NULL;
	struct TCB_t* tmp = NULL;

	// find number of pre-allocated nodes in the linklist
	tmp = *head;
	while(tmp != NULL)
	{
		pre_alloc_num++;
		tmp = tmp->next;
	}

	
	// allocating the memory for the node and add it  to the linklist
	for(i = 0; i < (num-pre_alloc_num);i++)
	{
		new = (struct TCB_t*)malloc(sizeof(struct TCB_t));
		// Initializing the strucure
		new->assignPriority 	= -1;
		new->currPriority	= -1;
		new->wcet		= 0.0;
		new->deadline		= 0.0;
		new->period		= 0.0;
		new->next		= NULL;

		// Adding the node to the linklist
		if(*head == NULL){
			*head = new;
			tmp   = new;
		}
		else{
			tmp->next = new;
			tmp = tmp->next;
		}


	}

}





/* 
 *  This function frees the extra nodes in the linklist
 *  and re-initializes the first num nodes of the list 
 */ 
void destroy_tcb_init(struct TCB_t** head, int num)
{
	int list_len = 0;
	int i = 0;
	
	struct TCB_t*	tmp;
	struct TCB_t*	free_ptr;

	tmp = *head;

	// finds the length of the list
	while(tmp != NULL){
		list_len++;
		tmp = tmp->next;
	}

	// re-initialize the node and place the pointer after which we 
 	// free the list
	if( list_len  > num)
	{
		tmp = *head;
		for(i = 0;i < num;i++){
			tmp->assignPriority 	= -1;
			tmp->currPriority	= -1;
			tmp->wcet 		= 0.0;
			tmp->deadline		= 0.0;
			tmp->period  		= 0.0;
	
			if(i == num -1)
				tmp->next = NULL;

			tmp = tmp->next;
		}

	}

	// Free the list after and including the tmp pointer
	while(tmp != NULL)
	{
		free_ptr = tmp;
		tmp = tmp->next;
		free(free_ptr);
	}

	// If the num = 0 then we make head = NULL
	if(num == 0)
		*head = NULL;

}	
