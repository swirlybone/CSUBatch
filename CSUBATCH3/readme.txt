To run the program, simply typing "make" without quotations will compile main and run main.

This program allows you to submit a job with a time and priority into a queue with "run", where jobs
are then executed by a dispatching module. A scheduling module is used to schedule the jobs
by order of different algorithms, such as fcfs, sjf, and priority. 

"quit" quits the program and gives information on the session as you exit while "help" displays
the options you can choose in the program. "list" displays information on all current jobs.

"test" is supposed to allow you to input several parameters in order to evaluate the efficiency of
different scheduling policies. Currently, just typing "test" gives the print statement, but adding
any more gives "Command not found", which we cannot determine the cause of at the moement. It seems
related to cmd_dispatch in the commandline.c file, where the for loop right before this print statement
may be causing the issue. Otherwise, it may be due to an issue with cmdtable.

TODO: Figure out the issue with test function implementation, have jobs that are currently running
say running in the list, and fix an issue where the run function will sometimes not add job information
to the list. 

Readme by Michael Hamm
Edited by Trevon Harris

