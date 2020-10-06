/*
 * Trevon Harris & Michael Hamm
 * September 28th 2020
 * Final touches done October 4, 2020
 * Dispatch code
 * The dispatch will handle execution of batch files pulled from queue 
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "Queue.h"
#include "Dispatch.h"


void *nextJob(){

  while(1){
	  //Locks the threads
    pthread_mutex_lock(&queMutex);

	//Wait for queue to no longer be empty
    while( isEmpty(jobQueue) ){
        pthread_cond_wait(&jobsInQue, &queMutex);
    }

    struct job nextjob = removeJob(jobQueue);

    //Meant to inform threads if its full or not
    pthread_cond_signal(&queNotFull);

    //Unlocks threads
    pthread_mutex_unlock(&queMutex);

    char * name = nextjob.jobName;
    char * args[] = {name,NULL};
    ejob(args);

  }

}



//Performs given job
void ejob(char *args[]){

  pid_t pid;

  pid = fork();


  if (pid == -1) {
	  //Debugger
    puts("Error with the fork.");
  } else if (pid == 0) {
    execv(args[0], args);
  }
  else{
    wait(NULL);
  }

}


