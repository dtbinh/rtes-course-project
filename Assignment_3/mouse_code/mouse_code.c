#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define DEBUG	0
#define MOUSEFILE "/dev/input/mouse0"


int main()
{
	int i;
	int x  = 0, y = 0;
	int toggle  = 0;
	int fd;

	unsigned char* ptr = NULL;
	unsigned char* prev_ptr = NULL;

	struct input_event ie;

	// Opening device file
	if((fd = open(MOUSEFILE, O_RDONLY)) == -1) 
	{
		perror("opening device");
	    	exit(EXIT_FAILURE);
	}

		
	// Reading from mouse
	while(read(fd, &ie, sizeof(struct input_event))) 
	{
		ptr = (unsigned char*)&ie;
	
	#if DEBUG == 0
		// For mouse click
		if(*ptr == 0x09){
			printf("Left Mouse click \n");
			toggle = toggle ^ 1;
			printf("Toggle = %d \n",toggle);
		}
		else if(*ptr == 0x0A)
			printf("Right Mouse click \n");

		if(toggle == 1)
		{
			// For mouse movement
			if(*ptr == 0x08 && *(ptr+1) == 0x00 && *(ptr+2) == 0x01)
				y++;
			else if(*ptr == 0x08 && *(ptr+1) == 0x01 && *(ptr+2) == 0x00)
				x++;
			else if(*ptr == 0x18)
				x--;
			else if(*ptr == 0x28)
				y--;
		   	printf("%d %d\n",x,y);	   
		}
		else{
			// Block tragectory 
		}
	#endif

	// Printing the hexadecimal bit stream
	#if DEBUG == 1
		for(i=0; i<sizeof(ie); i++)
		        printf("%02X ", *ptr++);
		printf("\n");
	#endif

		
	}

return 0;
}
