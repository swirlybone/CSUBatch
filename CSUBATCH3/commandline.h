/*
 * Trevon Harris & Michael Hamm
 * September 28th 2020
 * Final touches done October 4, 2020
 * Header file for commandline
*/
#ifndef  COMMANDLINE_H
#define  COMMANDLINE_H

//Runs command
int cmd_run(int nargs, char **args, struct jobQ* jobQueue);

//Runs benchmark
int cmd_test(int narg, char** args, struct jobQ* jobQueue);

//Quit command
int cmd_quit(int nargs, char **args, struct jobQ* jobQueue);

//Help command
int cmd_helpmenu(int n, char **a, struct jobQ* jobQueue);

//Show menu command
void showmenu(const char *name, const char *x[]);

//Policy switch
int cmd_schedule_policy(int narg, char** args, struct jobQ* jobQueue);

//List of jobs in action
int cmd_list(int narg, char** args, struct jobQ* jobQueue);

//Dispatch
int cmd_dispatch(char *cmd, struct jobQ* jobQueue);


#endif


