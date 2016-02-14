/* filename:   main.c
 * author:     Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 2
 *
 * This file contains the main function and all functions that are not 
 * a part of the priority queue ADT or fifo queue ADT.
 */

#include <ctype.h>
#include <string.h>
#include "cpu_sim.h"

int main(int argc, char *argv[]) {
	settings s;
	char buffer[128];
	process * p_adt = NULL;
	pQueue pq = NULL;
	queue fq = NULL;
	int i;
	s.v = 0;
	s.d = 0;
	s.r = -1;

	for(i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-d") == 0) {
			s.d = 1;
		} else if(strcmp(argv[i], "-v") == 0) {
			s.v = 1;
		} else if(strcmp(argv[i], "-r") == 0) {
			sscanf(argv[i+1], "%d", &s.r);
		}
	}

	fgets(buffer, 128, stdin);
	sscanf(buffer, "%d %d %d", &s.process_count, &s.thread_switch, &s.process_switch);

	parseProcesses(stdin, &p_adt, s);

	if(s.v) printProcesses(p_adt, s);

	pq = pQueue_init(8);
	fq = fifoQ_init();

	fillPriorityQueue(pq, p_adt, s);
	fillFIFOQueue(fq, p_adt, s);
	if(s.r == -1) {
		fcfs(p_adt, pq, s);
	} else {
		rr(p_adt, fq, s);
	}

	freeProcesses(p_adt, s);

}


void parseProcesses(FILE *fp, process **p_adt, settings s) {
	int i, j;  /* iterators */
	char buffer[128];
	int process_ID = 0;
	int thread_count = 0;
	thread * temp;

	*p_adt = malloc(sizeof(process) * s.process_count); // might not allow array access

	for(i = 0; i < s.process_count; i++) {
		fgets(buffer, 128, fp);
		sscanf(buffer, "%d %d", &process_ID, &thread_count);
		
		(*p_adt)[i].thread_count = thread_count;
		(*p_adt)[i].process_ID = process_ID;

		(*p_adt)[i].child_thread = malloc(sizeof(thread) * thread_count);

		for(j = 0; j < thread_count; j++) {
			temp = &(*p_adt)[i].child_thread[j];
			parseThread(fp, &temp);
			temp->i = -1;
			(*p_adt)[i].child_thread[j].parent_process = &(*p_adt)[i];
		}
	}
}

void parseThread(FILE *fp, thread **t) {
	int i;
	char buffer[128];

	fgets(buffer, 128, fp);
	sscanf(buffer, "%d %d %d", &(*t)->thread_ID, &(*t)->arrival_time, &(*t)->burst_count);
	(*t)->child_burst = malloc(sizeof(burst) * (*t)->burst_count);
	for(i = 0; i < ((*t)->burst_count - 1); i ++) {
		fgets(buffer, 128, fp);
		sscanf(buffer, "%d %d %d", &(*t)->child_burst[i].burst_ID, &(*t)->child_burst[i].cpu_time, &(*t)->child_burst[i].io_time);
		(*t)->child_burst[i].cpu_remain = (*t)->child_burst[i].cpu_time;
		(*t)->child_burst[i].parent_thread = (*t);
	}
	fgets(buffer, 128, fp);
	sscanf(buffer, "%d %d", &(*t)->child_burst[i].burst_ID, &(*t)->child_burst[i].cpu_time);
	(*t)->child_burst[i].cpu_remain = (*t)->child_burst[i].cpu_time;
	(*t)->child_burst[i].io_time = 0;
}

void fillPriorityQueue(pQueue pq, process *p_adt, settings s) {
	int i, j;
	for(i = 0; i < s.process_count; i++) {
		for(j = 0; j < p_adt[i].thread_count; j++) {
			p_adt[i].child_thread[j].state = NEW;
			pQueue_push(pq, &p_adt[i].child_thread[j], p_adt[i].child_thread[j].arrival_time);
		}
	}
}

void fillFIFOQueue(queue fq, process *p_adt, settings s) {
	int i, j;
	for(i = 0; i < s.process_count; i++) {
		for(j = 0; j < p_adt[i].thread_count; j++) {
			p_adt[i].child_thread[j].state = NEW;
			fifoQ_push(fq, &p_adt[i].child_thread[j]);
		}
	}
}



void printProcesses(process *p_adt, settings s) {
	int i,j,k;
	process * p;
	thread * t;
	burst * b;
	printf("Print out of parsed data\n");
	printf("Originally just a test function\n");
	printf("Printed because Verbose was specified\n\n");
	printf("**************************\n");
	printf("Process Count: %d\n",s.process_count);
	printf("**************************\n\n");

	for(i = 0; i < s.process_count; i++) {
		p = &p_adt[i];
		printf("**************************\n");
		printf("Process ID: %d\n",p->process_ID);
		printf("Threads:    %d\n",p->thread_count);
		printf("**************************\n");

		for(j = 0; j < p->thread_count; j++) {
			t = &p->child_thread[j];
			printf("- Thread ID:    %d\n",t->thread_ID);
			printf("- Arrival Time: %d\n",t->arrival_time);
			printf("- CPU Bursts:   %d\n",t->burst_count);

			for(k = 0; k < t->burst_count; k++) {
				b = &t->child_burst[k];
				printf("  - CPU Burst ID: %d\n",b->burst_ID);
				printf("  - CPU Time:     %d\n",b->cpu_time);
				printf("  - I/O Time:     %d\n",b->io_time);

			}
		}
	}
	printf("\n\n");
}

void freeProcesses(process *p_adt, settings s) {
	int i,j;

	for(i = 0; i < s.process_count; i++) {
		for(j = 0; j < p_adt[i].thread_count; j++) {

			#ifdef _DEBUG_
			printf("Freeing bursts for Process %d Thread %d...\n", i+1, j+1);
			#endif
			free(p_adt[i].child_thread[j].child_burst);
		}

		#ifdef _DEBUG_
		printf("Freeing threads for Process %d...\n", i+1);
		#endif
		free(p_adt[i].child_thread);
	}

	#ifdef _DEBUG_
	printf("Freeing Processes...\n");
	#endif
	free(p_adt);
	p_adt = NULL;
}

void fcfs(process *p_adt, pQueue readyQ, settings s) {

	int current_time = 0;
	int idle_time = 0;
	thread * currThread = NULL;
	thread * temp = NULL;
	int prev_process_ID = 0;
	int prev_thread_ID = 0;
	pQueue blockedQ;
	blockedQ = pQueue_init(4);

	while(1) {
		if(validTopItem(readyQ, current_time)) {

			currThread = pQueue_pop(readyQ,NULL);

			if (currThread->state == NEW) {
				if(s.v) printf("At time %d: Thread %d of Process %d moves from NEW to READY\n", current_time, currThread->thread_ID, currThread->parent_process->process_ID);
			}
			currThread->state = READY;

			/* Compute overhead */
			if(currThread->parent_process->process_ID != prev_process_ID) {
				current_time += s.process_switch;
			} else if(currThread->thread_ID != prev_thread_ID) {
				current_time += s.thread_switch;
			}

			/* READY -> RUNNING */
			if(s.v) printf("At time %d: Thread %d of Process %d moves from READY to RUNNING\n", current_time, currThread->thread_ID, currThread->parent_process->process_ID);
			currThread->state = RUNNING;
			currThread->i++;
			current_time += currThread->child_burst[currThread->i].cpu_time;
			prev_thread_ID = currThread->thread_ID;
			prev_process_ID = currThread->parent_process->process_ID;

			if(currThread->child_burst[currThread->i].io_time != 0) {
				/* RUNNING -> BLOCKED */
				currThread->state = BLOCKED;
				if(s.v) printf("At time %d: Thread %d of Process %d moves from RUNNING to BLOCKED\n", current_time, currThread->thread_ID, currThread->parent_process->process_ID);
				pQueue_push(blockedQ, currThread, currThread->child_burst[currThread->i].io_time + current_time);
			} else if(currThread->i == (currThread->burst_count - 1)) {
				/* RUNNING -> TERMINATED */
				if(s.v) printf("At time %d: Thread %d of Process %d moves from RUNNING to TERMINATED\n", current_time, currThread->thread_ID, currThread->parent_process->process_ID);
				currThread->state = TERMINATED;
				currThread->finish_time = current_time;
				if(allThreadsTerminated(p_adt, s)) {
					break;
				}
			}

		} else {
			current_time++;
			idle_time++;
		}

		while(validTopItem(blockedQ, current_time)) {
			temp = pQueue_pop(blockedQ, NULL);
			/* BLOCKED -> READY */
			if(s.v) printf("At time %d: Thread %d of Process %d moves from BLOCKED to READY\n", current_time, temp->thread_ID, temp->parent_process->process_ID);
			temp->state = READY;
			pQueue_push(readyQ, temp, temp->arrival_time);
		}
	}

	printf("FCFS: \n\n");
	printf("Total Time Required is %d time units\n", current_time);
	turnAroundTime(p_adt, s, current_time, 1);
	printf("CPU Utilization is %d%%\n\n",((current_time - idle_time)*100)/current_time);
	if(s.d) turnAroundTime(p_adt, s, current_time, 0);

}

void rr(process *p_adt, queue readyQ, settings s) {

	int current_time = 0;
	int idle_time = 0;
	thread * currThread = NULL;
	thread * temp = NULL;
	int prev_process_ID = 0;
	int prev_thread_ID = 0;
	pQueue blockedQ;
	blockedQ = pQueue_init(4);

	while(1) {
		if(readyQ->head != NULL) {

			currThread = fifoQ_pop(readyQ);

			if (currThread->state == NEW) {
				if(s.v) printf("At time %d: Thread %d of Process %d moves from NEW to READY\n", current_time, currThread->thread_ID, currThread->parent_process->process_ID);
				currThread->i++;
			}
			currThread->state = READY;

			/* Compute overhead */
			if(currThread->parent_process->process_ID != prev_process_ID) {
				current_time += s.process_switch;
			} else if(currThread->thread_ID != prev_thread_ID) {
				current_time += s.thread_switch;
			}

			/* READY -> RUNNING */
			if(s.v) printf("At time %d: Thread %d of Process %d moves from READY to RUNNING\n", current_time, currThread->thread_ID, currThread->parent_process->process_ID);
			currThread->state = RUNNING;
			prev_thread_ID = currThread->thread_ID;
			prev_process_ID = currThread->parent_process->process_ID;

			if(currThread->child_burst[currThread->i].cpu_remain > s.r) {
				current_time += s.r;
				currThread->child_burst[currThread->i].cpu_remain -= s.r;
				if(s.v) printf("At time %d: Thread %d of Process %d moves from RUNNING to READY\n", current_time, currThread->thread_ID, currThread->parent_process->process_ID);
				currThread->state = READY;
				fifoQ_push(readyQ, currThread);
			} else {
				current_time += currThread->child_burst[currThread->i].cpu_remain;
				if(currThread->child_burst[currThread->i].io_time != 0) {
					/* RUNNING -> BLOCKED */
					currThread->state = BLOCKED;
					if(s.v) printf("At time %d: Thread %d of Process %d moves from RUNNING to BLOCKED\n", current_time, currThread->thread_ID, currThread->parent_process->process_ID);
					pQueue_push(blockedQ, currThread, currThread->child_burst[currThread->i].io_time + current_time);
					currThread->i++;
				} else if(currThread->i == (currThread->burst_count - 1)) {
					/* RUNNING -> TERMINATED */
					if(s.v) printf("At time %d: Thread %d of Process %d moves from RUNNING to TERMINATED\n", current_time, currThread->thread_ID, currThread->parent_process->process_ID);
					currThread->state = TERMINATED;
					currThread->finish_time = current_time;
					if(allThreadsTerminated(p_adt, s)) {
						break;
					}
				}
			}

		} else {
			current_time++;
			idle_time++;
		}

		while(validTopItem(blockedQ, current_time)) {
			temp = pQueue_pop(blockedQ, NULL);
			/* BLOCKED -> READY */
			if(s.v) printf("At time %d: Thread %d of Process %d moves from BLOCKED to READY\n", current_time, temp->thread_ID, temp->parent_process->process_ID);
			temp->state = READY;
			fifoQ_push(readyQ, temp);
		}
	}

	printf("Round Robin (quantum = %d time units): \n\n", s.r);
	printf("Total Time Required is %d time units\n", current_time);
	turnAroundTime(p_adt, s, current_time, 1);
	printf("CPU Utilization is %d%%\n\n",((current_time - idle_time)*100)/current_time);
	if(s.d) turnAroundTime(p_adt, s, current_time, 0);

}


/*
This function checks if the top item of the passed priority queue is valid.
Returns 1 for true and 0 for false.
*/
int validTopItem(pQueue pq, int cTime) {
	thread * t;
	int key;

	t = pQueue_top(pq, &key);
	if(t != NULL) {
		if(key <= cTime) {
			return 1;
		}
	}
	return 0;
}

int allThreadsTerminated(process * p_adt, settings s) {
	int i, j;
	for(i = 0; i < s.process_count; i++) {
		for(j = 0; j < p_adt[i].thread_count; j++) {
			if(p_adt[i].child_thread[j].state != TERMINATED) {
				return 0;
			}
		}
	}

	return 1;
}

void getBurstSums(thread t, int *service, int *io) {
	int i;

	for(i = 0; i < t.burst_count; i++) {
		*service += t.child_burst[i].cpu_time;
		*io += t.child_burst[i].io_time;
	}
}

void turnAroundTime(process * p_adt, settings s, int cTime, int average) {
	int i, j;
	int sum = 0, count = 0, dif = 0, service = 0, io = 0;
	float out = 0.0;

	for(i = 0; i < s.process_count; i++) {
		for(j = 0; j < p_adt[i].thread_count; j++) {
			dif = p_adt[i].child_thread[j].finish_time - p_adt[i].child_thread[j].arrival_time;
			sum += dif;
			count ++;
			if (!(average)) {
				printf("Thread %d of Process %d:\n\n",j+1, i+1);
				printf("arrival time: %d\n", p_adt[i].child_thread[j].arrival_time);
				getBurstSums(p_adt[i].child_thread[j], &service, &io);
				printf("service time: %d units\n", service);
				printf("I/O time: %d units\n", io);
				printf("turnaround time: %d units\n", dif);
				printf("finish time: %d units\n\n", p_adt[i].child_thread[j].finish_time);
			}
		}
	}
	if(average) {
		out = (float)sum / (float)count;
		printf("Average turnaround Time is %.1f time units\n",out);
	}
}


