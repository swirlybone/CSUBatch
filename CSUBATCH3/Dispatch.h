/*
 * Trevon Harris & Michael Hamm
 * September 28th 2020
 * Final touches done October 4, 2020
 * Header file for the dispatch
*/
//Calls on variables from main.c
extern pthread_cond_t jobsInQue;
extern pthread_cond_t queNotFull;
extern pthread_mutex_t queMutex;
extern struct jobQ* jobQueue;

void ejob(char * args[]);

void *nextJob();


