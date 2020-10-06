/*
 * Trevon Harris & Michael Hamm
 * September 28th 2020
 * Final touches done October 4, 2020
 * Handles queue sorting and storing
 */
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

//Function to create jobs
struct jobQ* buildJobQ(int capacity){
	struct jobQ* jobQueue = (struct jobQ*) malloc(sizeof(struct jobQ));
	jobQueue->numJobs = capacity;
	jobQueue->size = 0;
	jobQueue->first = 0;
	jobQueue->last = capacity - 1;
	jobQueue->policy = "fcfs";
	jobQueue->schedInt = 3;
	jobQueue->jobs = (struct job*) malloc(sizeof(struct job) * jobQueue->numJobs);
	return jobQueue;
}

//Full checker function
int isFull(struct jobQ* jobQ){
	return (jobQ->size == jobQ->numJobs);
}
int isEmpty(struct jobQ* jobQ){
	return (jobQ->size == 0);
}
/*
 *Adds a job to the job queue
 */
void addJob(struct jobQ* jobQ, struct job job){
	if(isFull(jobQ)){
		printf("The job queue is full.");
	}
	jobQ->last = (jobQ->last + 1) % jobQ->numJobs;
	jobQ->jobs[jobQ->last] = job;
	jobQ->size++;
	//This block sorts the queue according to the current scheduling policy after the job is added
	//this allows the order of the job queue to comply with the current scheduling policy
	if(jobQ->schedInt == 1){
		quickSort(jobQ->jobs, 0, jobQ->size - 1, 1);
	}else if(jobQ->schedInt == 2){
		quickSort(jobQ->jobs, 0, jobQ->size - 1, 2);
	}else if(jobQ->schedInt == 3){
		quickSort(jobQ->jobs, 0, jobQ->size - 1, 3);
	}
}

//Function to remove job from queue
struct job removeJob(struct jobQ* jobQ){
	struct job job;
	if(isEmpty(jobQ)){
		printf("Job queue is emtpy.\n");
		exit(1);
	}
	job = jobQ->jobs[jobQ->first];
	jobQ->first = (jobQ->first + 1) % jobQ->numJobs;
	jobQ->size --;
	return job;

}


//Function to display the queue
void printQ(struct jobQ* jobQ){
	if(isEmpty(jobQ)){
		printf("Job queue is empty.\n");
	}else{
		struct job* jobs = jobQ->jobs;
		int i = 0;
		printf("Name\CPU time\tPri\tArrival Time\tProgress\n");
		for(i = 0; i < jobQ->size; ++i){
			printf("%s\t  %i\t\t%i\t%i\t\t%s\n", jobQ->jobs[i].jobName, jobQ->jobs[i].timeToComplete, jobQ->jobs[i].priority, jobQ->jobs[i].arrivalTime,
			jobQ->jobs[i].progress);

		}
	}
}

void swap(struct job* a, struct job* b) {
    struct job t = *a;
    *a = *b;
    *b = t;
}

int partition (struct job arr[], int low, int high, int policy) {
    struct job pivot = arr[high];
    int i = (low - 1);
	int j;
	//The SJF
	if(policy == 1){
		for (j = low; j <= high- 1; j++) {
        	if (arr[j].timeToComplete < pivot.timeToComplete) {
            	i++;
            	swap(&arr[i], &arr[j]);
        	}
    	}
		//Priority
	}else if(policy == 2){
		for (j = low; j <= high- 1; j++) {
        	if (arr[j].priority < pivot.priority) {
            	i++;
            	swap(&arr[i], &arr[j]);
        	}
    	}
		//The FCFS
	}else if(policy == 3){
		for (j = low; j <= high- 1; j++) {
        	if (arr[j].arrivalTime < pivot.arrivalTime) {
            	i++;
            	swap(&arr[i], &arr[j]);
        	}
    	}
	}

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(struct job arr[], int low, int high, int policy) {
    if (low < high){
        int pi = partition(arr, low, high, policy);

        quickSort(arr, low, pi - 1,policy);
        quickSort(arr, pi + 1, high, policy);
    }
}


