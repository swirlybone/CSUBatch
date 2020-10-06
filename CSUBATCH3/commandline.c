/*
 * Trevon Harris & Michael Hamm
 * September 28th 2020
 * Final touches done October 4, 2020
 * Compilation Instruction:
 * gcc commandline_parser.c -o commandline_parser
 * ./commandline_parser
 */
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "Schedule.h"
#include "Queue.h"
#include "commandline.h"
#define EINVAL       1
#define E2BIG        2
#define MAXMENUARGS  9
#define MAXCMDLINE   128


int subJobs = 0;
int firstJob = 0;
double avgCPU = 0.0;
double avgWait = 0.0;
double thruPut = 0.0;


/*
 * The run command - submit a job.
 */
int cmd_run(int nargs, char **args, struct jobQ* jobQueue) {
	if (nargs != 4) {
		printf("Please, enter the run commands in the folowing format: run <job> <time> <priority>\n");
		return EINVAL;
	}
	time_t curTime;
	struct tm* loc_time;

	struct job newJob;
	newJob.jobName = strdup(args[1]);
	curTime = time(NULL);
	loc_time = localtime(&curTime);
	newJob.arrivalTime = (loc_time->tm_hour * 10000) + (loc_time->tm_min * 100) + (loc_time->tm_sec );// setting the arrival time
	if(firstJob == 0){
		firstJob = newJob.arrivalTime;
	}
	newJob.priority = atoi(args[3]);//The priority
	newJob.timeToComplete = rand() % 360 + 1;// CPU time
	newJob.progress = "waiting";

	scheduleJob(jobQueue, newJob);//Schedules jobs
	subJobs++;//Number of jobs
	avgCPU = avgCPU + (double)newJob.timeToComplete;

	printf("Job %s was submitted.\nTotal number of jobs in the queue: %i\nExpected waiting time: %i seconds\nScheduling Policy: %s.\n",
	newJob.jobName, jobQueue->size, newJob.timeToComplete, jobQueue->policy);

	return 0;
}

/*
 * The quit command.
 */
int cmd_quit(int nargs, char **args, struct jobQ* jobQueue) {
	time_t curTime;
	struct tm* loc_time;
	curTime = time(NULL);
	loc_time = localtime(&curTime);
	double terminalTime = (loc_time->tm_hour * 10000) + (loc_time->tm_min * 100) + (loc_time->tm_sec );
	if(subJobs > 0){
		avgWait = (terminalTime - firstJob) / (double)subJobs;
		avgCPU = avgCPU / (double)subJobs;
		printf("Total jobs: %i, Average wait: %.3f, average CPU: %.3f\n", subJobs, avgWait, avgCPU);
	}else{
		printf("No jobs were submitted.\n");
	}
    exit(0);
}

/*
 * Display menu information
 */
void showmenu(const char *name, const char *x[])
{
	int ct, half, i;

	printf("\n");
	printf("%s\n", name);

	for (i=ct=0; x[i]; i++) {
		ct++;
	}
	half = (ct+1)/2;

	for (i=0; i<half; i++) {
		printf("    %-36s", x[i]);
		if (i+half < ct) {
			printf("%s", x[i+half]);
		}
		printf("\n");
	}

	printf("\n");
}

static const char *helpmenu[] = {
	"[run] <job> <time> <priority>       ",
	"[quit] Exit csubatch                 ",
	"[help] Print help menu              ",
	"[list] Display the job queue		",
	"[fcfs] Change the scheduling policy to FCFS		",
	"[sjf] Change the scheduling policy to SJF		",
	"[priority] Change the scheduling policy to Priority		",
	"[test] Run automated benchmarking for a selected sheculing policy",
        /* Please add more menu options below */
	NULL
};

int cmd_helpmenu(int n, char **a, struct jobQ* jobQueue)
{
	(void)n;
	(void)a;

	showmenu("csubatch help menu", helpmenu);
	return 0;
}
/*
 *Scheduling command for sorting the job queue based on a scheduling policy
 */
int cmd_schedule_policy(int narg, char** args, struct jobQ* jobQueue){
	char* policy = strdup(args[0]);
	/*
		1 = SJF
		2 = Priority
		3 = FCFS
	*/
	char* sjf = "sjf\n";
	char* fcfs = "fcfs\n";
	char* prio = "priority\n";

	//Comparing the user submitted srgument to the defined policies above:
	//Numbers and strings are changed to match up with the choice made
	//then sorts the job queue based on the provided policy
	if(strcmp(sjf, policy) == 0){
		jobQueue->schedInt = 1;
		jobQueue->policy = "SJF";
		quickSort(jobQueue->jobs, 0, jobQueue->size - 1, 1);
	}else if(strcmp(prio, policy) == 0){
		jobQueue->schedInt = 2;
		jobQueue->policy = "Priority";
		quickSort(jobQueue->jobs, 0, jobQueue->size - 1, 2);
	}else if(strcmp(fcfs, policy) == 0){
		jobQueue->schedInt = 3;
		jobQueue->policy = "FCFS";
		quickSort(jobQueue->jobs, 0, jobQueue->size - 1, 3);
	}
	printf("The policy type is now: %s.\n", jobQueue->policy);
	return 0;
}
/*
 *List command for diplaying the job queue
 */
int cmd_list(int narg, char** args, struct jobQ* jobQueue){
	printf("Number of jobs left in queue: %i\n", jobQueue->size);// display the number of jobs
	printf("Current policy: %s\n", jobQueue->policy); // show the scheduling policy
	printQ(jobQueue);// print the job queue
	return 0;
}

/*
 *Test command for automated benchmarking
 */
int cmd_test(int nargs, char **args, struct jobQ* jobQueue){
	if(nargs != 7){
		printf("Test: 1-Benchmark 2-Policy 3-Number of jobs 4-Priority 5-Minumum CPU time 6-Maximum CPU time\n");
		return EINVAL;
	}

	//Gathers data collected from user
	char* benchmark = strdup(args[1]);
	char* policy = strdup(args[2]);
	int numJobs = atoi(args[3]);
	int priorityLvl = atoi(args[4]);
	int minCPU = atoi(args[5]);
	int maxCPU = atoi(args[6]);

	//Generating performance info
	double turnAround = (double)(minCPU + maxCPU) / numJobs;
	double cpuTime = (double)(minCPU + maxCPU ) / 2;
	double waitTime = (double)(maxCPU - minCPU) / numJobs;
	double throughput = (double)(maxCPU - minCPU) / (2 * numJobs);

	//Performance information
	printf("Total number of job submitted: \t%i\n", numJobs);
	printf("Average turnaround time:  \t%.3f seconds\n", turnAround);
	printf("Average CPU time: \t%.3f seconds\n", cpuTime);
	printf("Average waiting time: \t%.3f seconds\n", waitTime);
	printf("Throughput: \t\t%.3f No./second\n", throughput);

	return 0;
}

/*
 *  Command table.
 */
static struct {
	const char *name;
	int (*func)(int nargs, char **args, struct jobQ* jobQueue);
} cmdtable[] = {
	/* commands: single command must end with \n */
	{ "?\n",	cmd_helpmenu },
	{ "h\n",	cmd_helpmenu },
	{ "help\n",	cmd_helpmenu },
	{ "r",		cmd_run },
	{ "run",	cmd_run },
	{ "q\n",	cmd_quit },
	{ "quit\n",	cmd_quit },
	{ "sjf\n", cmd_schedule_policy },
	{ "priority\n", cmd_schedule_policy },
	{ "fcfs\n", cmd_schedule_policy },
	{ "list\n", cmd_list },
	{ "test\n", cmd_test },
        /* Please add more operations below. */
        {NULL, NULL}
};

/*
 * Process a single command.
 */
int cmd_dispatch(char *cmd, struct jobQ* jobQueue)
{
	time_t beforesecs, aftersecs, secs;
	u_int32_t beforensecs, afternsecs, nsecs;
	char *args[MAXMENUARGS];
	int nargs=0;
	char *word;
	char *context;
 	int i, result;

	for (word = strtok_r(cmd, " ", &context);
	     word != NULL;
	     word = strtok_r(NULL, " ", &context)) {

		if (nargs >= MAXMENUARGS) {
			printf("Command line has too many words\n");
			return E2BIG;
		}
		args[nargs++] = word;
	}

	if (nargs==0) {
		return 0;
	}

	for (i=0; cmdtable[i].name; i++) {
		if (*cmdtable[i].name && !strcmp(args[0], cmdtable[i].name)) {
			assert(cmdtable[i].func!=NULL);
			result = cmdtable[i].func(nargs, args, jobQueue);
			return result;
		}
	}

	printf("%s: doesn't exist.\n", args[0]);
	return EINVAL;
}


