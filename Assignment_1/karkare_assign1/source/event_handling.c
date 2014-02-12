#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <sys/select.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>

#include "../include/structures.h"


#define DIR_PATH	"/dev/input/by-path/"

extern struct event_list*	elist[10];
extern pthread_barrier_t	activation;
extern pthread_barrier_t	completion;
extern volatile int		condition_variable;



/*
 *  This function iterates over all the device present in the /dev/input/by-path/
 *   directory and returns all the filename ending with kbd seperated by ":".
 */ 
void get_kbd_event_filename(char* filename)
{
	struct dirent* dp;
	DIR*	dir;

	int tmp;
	int i = 0;

	// Opening the directory to search for the kbd devide file	
	dir = opendir(DIR_PATH);
	if(!dir)
	{
		printf("Error reading keyboard deveice file \n");
		printf("Error: %s \n",strerror(errno));
		exit(1);
	}

	while ((dp=readdir(dir)) != NULL)
	{
		tmp = strlen(dp->d_name);
		if(dp->d_name[tmp-1] == 'd' && dp->d_name[tmp-2] == 'b' && dp->d_name[tmp-3] == 'k'){
			if(i == 0)
				strcpy(filename,dp->d_name);
			else {
				strcat(filename,"$");
				strcat(filename,dp->d_name);
			}
			i++;
		}
	}

	closedir(dir);

}

/*
 *  This function sends the SIGUSR1 signal to all the threads 
 *  waiting on the event key_code
 */
void send_signal(int key_code)
{
	struct event_list* 	tmp;
	int event = (key_code - 1)%10;

	tmp = elist[event];

	while(tmp != NULL)
	{
		pthread_kill(tmp->tid,SIGUSR1);
		tmp = tmp->next;

	}


}


/*
 *  This function continuesly check for the event press button on the 
 *  keyboard and sends signals to all the threads registered for it.
 */

void event_handler()
{
	char* kbd_filename;
	char* kbd_file;
	char* saveptr;
	char* kbd_fullpathname;

	int   i = 0;
	int   top;
	int   fd[5];
	int   active_fd;

	struct input_event ev;

	fd_set	set;

	kbd_filename 	 = (char*)malloc(sizeof(char)*200);		
	kbd_fullpathname = (char*)malloc(sizeof(char)*250);
	
	// Getting the keyboard device file names
	get_kbd_event_filename(kbd_filename);

	// Extracting the individual filename from the return filename and opening them for reading
	kbd_file = strtok_r(kbd_filename,"$",&saveptr);
	while(kbd_file)
	{
		strcpy(kbd_fullpathname,DIR_PATH);
		strcat(kbd_fullpathname,kbd_file);
		fd[i] = open(kbd_fullpathname,O_RDONLY);
		if(fd[i] == -1){
			kbd_file = strtok_r(NULL,"$",&saveptr);
			continue;
		}
		FD_SET(fd[i],&set);
		i++;
		kbd_file = strtok_r(NULL,"$",&saveptr);
	}
	if(i == 0){
		printf("Error opening any Keyboard device file \n");
		printf("Error: %s \n",strerror(errno));
		exit(1);
	}
	
	top = i-1;

	pthread_barrier_wait(&activation);

	// Waiting for the read on all the keyboards 
	while(condition_variable)
	{
		select(fd[top] + 1,&set,NULL,NULL,NULL);	

		// Checking which keyboard generated the input and read from it
		for(i = 0;i <= top;i++){
			if(FD_ISSET(fd[i],&set) != 0)
				active_fd = fd[i];
		}

		// reading from the keyboard structure
		read(active_fd,&ev,sizeof(struct input_event));

		if(ev.type == 1 && ev.value == 1){
			if( ev.code >= 2 && ev.code  <= 11){
				send_signal(ev.code);
			}
			
		}		
	}

	pthread_barrier_wait(&completion);
		

	// Freeing the memory allocated
	if(kbd_filename)
		free(kbd_filename);
	if(kbd_fullpathname)
		free(kbd_fullpathname);

	// Closing all the opened files
	for(i = 0; i <= top;i++)
		close(fd[i]);

}


/*
 *  This function is used by the event task to register themselves 
 *  for receiving the signal when particular event happens
 */
void register_for_event(pthread_t tid , int event)
{
	struct event_list*	new;
	struct event_list*	tmp;

	new = (struct event_list*)malloc(sizeof(struct event_list));
	new->next = NULL;
	new->tid =  tid;

	if( elist[event] == NULL){
		elist[event] = new;
	}
	else
	{
		tmp = elist[event];
		while(tmp->next != NULL)
			tmp = tmp->next;

		tmp->next = new;
	}


}

