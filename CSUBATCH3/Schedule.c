/*
 * Trevon Harris & Michael Hamm
 * September 28th 2020
 * Final touches done October 4, 2020
 * Handles process scheduling in the batch system
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Queue.h"
#include "Schedule.h"
#include "commandline.h"

void *schedule_start(){

	while (1){
		char *input_str;
		size_t  input_size = 64;
		input_str = (char*) malloc(input_size * sizeof(char));
		if (input_str == NULL) {
				perror("Unable to malloc buffer");
				exit(1);
		}
		printf("~");
		getline(&input_str, &input_size, stdin); //Collects info 
		pthread_mutex_lock(&queMutex);//locks mutext when input is gathered
		cmd_dispatch(input_str, jobQueue);//sends info to dispatch
		pthread_mutex_unlock(&queMutex);//unlocks
	}
}
void scheduleJob(struct jobQ* jobQueue, struct job newJob){
	addJob(jobQueue, newJob);
	pthread_cond_signal(&jobsInQue);//lets other thread know something is in the queue

}


