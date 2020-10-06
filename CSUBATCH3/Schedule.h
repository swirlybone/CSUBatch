/*
 * Trevon Harris & Michael Hamm
 * September 28th 2020
 * Final touches done October 4, 2020
 * Header file for Schedule
*/
//Calls on variables from main.c
extern pthread_cond_t queNotFull;
extern pthread_mutex_t queMutex;
extern pthread_cond_t jobsInQue;
extern struct jobQ* jobQueue;
extern struct job newJob;

void *schedule_start();


void scheduleJob(struct jobQ* jobQueue, struct job newJob);

