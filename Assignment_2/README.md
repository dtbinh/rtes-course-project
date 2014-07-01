Schedulability Analysis 
================================================================

This directory contains 4 directories

1)./include      ---	 This directory contains two header file named "structures.h" and "config.h"
			 structures.h contains all the structures and function declarations used in the project.
			 config.h contains just two configuration option which changes the behaviour and the log level of the program.

2)./bin		 ---	 This directory will contain the binary executable of the project after the 
			 project is compiled properly.

3)./test	 --- 	 This directory contains the test cases file named input1.txt.
			 Along with the output_*_*.txt file which contains the results of the schedulability analysis
			 on the synthetic tasks.

4)./source	 ---	 This directory contains the .c file containig the definition of the function.
			 This directory contains 8 files:
			 a) main.c  ---  This file contains the main function from where the code starts.
			 b) tcb_functions.c  --- This file contains the function related to the creating and destroying of the linklist
						 which stores the task details.
			 c) edf_analysis.c   --- This file contains the function used to calculate the schedulability of a task set using EDF.
			 d) rm_analysis.c    --- This file contains the function used to calculate the schedulability of a task set using Rate Monotonic.
			 e) dm_analysis.c    --- This file contains the function used to calculate the schedulability of a task set using Deadline Monotonic.
			 f) fm_analysis.c    --- This file contains the function used to calculate the schedulability of a task set using Fixed Priority.
			 g) schedulability_analysis.c  --- This file contains the function used to calculate the schedulability using the synthetic task sets.
			 h) Makefile	     --- This file is used to compile the project and generate the binary exeutable.



Task 1 Compilation
==================================
To compile the project for Task 1
NOTE: go to the ../include/config.h file and change the LOG_LVL to 1 and MODE to 1

	$bash:~  make clean
	$bash:~  make main
This command will compile and generate the excutable in the ./bin folder with name main.

Task 1 Execution
=================================
To execute the Task 1project go the bin directory or use the fullpath :

if in ./bin folder
	`$bash:~ ./main < <input_filename>`

if in ./source folder
	`$bash:~  sudo ../bin/main <  <input_filename>`




Task 2 Compilation
==================================
To compile the project for Task 2
NOTE: go to the ../include/config.h file and change the LOG_LVL to 0 and MODE to 0

	$bash:~  make clean
	$bash:~  make main
This command will compile and generate the excutable in the ./bin folder with name main.


Task 2 Execution
=================================
To execute the Task 1project go the bin directory or use the fullpath :

if in ./bin folder
	`$bash:~ ./main `

if in ./source folder
	`$bash:~  ../bin/main`

NOTE: During execution of task 2 .. the program will output the name of the text file created in the ../test direcotry 
      and a message will appear when the computation is done.


Cleaning
================================
To clean the project directory go to the ./source directory and execute this command
$bash:~ make clean



						 						
