/*
 * Trevon Harris & Michael Hamm
 * September 28th 2020
 * Final touches done October 4, 2020
 * Main code for the CSUBatch
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Queue.h"
#include "commandline.h"
#include "Schedule.h"
#include "Dispatch.h"
#include	<unistd.h>


pthread_t thread_schedule, thread_dispatch;
pthread_mutex_t queMutex;//The mutex that will keep the threads from causing issues with queue
pthread_cond_t jobsInQue;//Informs us for jobs in queue
pthread_cond_t queNotFull;//Queue full checker
int status_schedule, status_dispatch; //Thread ID
struct jobQ* jobQueue;//Job structure

int main(){

	puts("El comienzo\n");

	jobQueue = buildJobQ(100);
	pthread_mutex_init(&queMutex,NULL);
	pthread_cond_init(&jobsInQue,NULL);
	pthread_cond_init(&queNotFull,NULL);

	//Help message
	puts("Use 'help' command to find out more about the CSU Batch commands");

	status_schedule = pthread_create(&thread_schedule, NULL, &schedule_start, NULL);
	if (status_schedule != 0) {
		//debugger
		puts("Schedule error");
		exit(-1);
	}


	//The thread is created and it calls the method nextJob with that thread
	status_dispatch = pthread_create(&thread_dispatch, NULL, &nextJob, NULL);
	if (status_dispatch != 0) {
		//debugger
		puts("Dispatch error");
		exit(-1);
	}


	//Ends the threads
	pthread_join(thread_schedule,NULL);
	pthread_join(thread_dispatch, NULL);
	return 0;
}


