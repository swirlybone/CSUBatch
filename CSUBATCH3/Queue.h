/*
 * Trevon Harris & Michael Hamm
 * September 28th 2020
 * Final touches done October 4, 2020
 * Header for queue
 */
#ifndef	QUEUE_H
#define QUEUE_H


struct job{
	int priority;
	int timeToComplete;
	int arrivalTime;
	char* jobName;
	char* progress;
};

struct jobQ{
	int first, last, size, numJobs;
	int schedInt;
	char* policy;
	struct job* jobs;
};

struct jobQ* buildJobQ(int capacity);
int isFull(struct jobQ* jobQ);
int isEmpty(struct jobQ* jobQ);
void addJob(struct jobQ* jobQ, struct job job);
struct job removeJob(struct jobQ* jobQ);
void printQ(struct jobQ* jobQ);
void swap(struct job* a, struct job* b);
int partition (struct job arr[], int low, int high, int policy);
void quickSort(struct job arr[], int low, int high, int policy);


#endif


