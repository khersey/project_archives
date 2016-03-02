/* filename:   memUtils.c
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 3
 *
 * Contains utility functions for memory management simulation.
 */

#include "holes.h"

/*
This function is repsonsible for swapping out the process which has been in memory the longest.
If the process has been swapped out 3 times already it is deallocated, othewise it is added back to the queue.
*/
void memorySwap(char *memory, queue inQ, queue swapQ) {
	process *swap;

	swap = (process *)fifoQ_pop(swapQ);
	memoryDelete(memory, swap);

	swap->count++;
	if(swap->count == 3) {	/* After 3 swaps out the process has completed */
		free(swap);
	} else {
		fifoQ_push(inQ, swap);
	}
}

/*
This function will write the process id of "p" to memory starting at the index "location".
*/
void memoryInsert(char *memory, int location, process *p) {
	int i;

	#ifdef _VERBOSE_
	printf("memoryInsert: called\n");
	#endif

	for(i = location; i < (location + p->size); i++) {
		if(i > 127) {
			printf("memoryInsert: FATAL ERROR - Array index out of range\n");
			exit(-1);
		}

		if(memory[i] != ' ') {
			printf("memoryInsert: ERROR - Memory Corruption!\n");
			printf("memoryInsert: memory at [%d] contains process %c\n",i+1,memory[i]);
		} else {
			memory[i] = p->id;
		}
		
	}

	#ifdef _VISUAL_
	printf("insert   process %c\n", p->id);
	#endif

}

/*
This function replaces all instances of the id of "p" with spaces.
*/
void memoryDelete(char *memory, process *p) {
	int i;

	#ifdef _VERBOSE_
	printf("memoryDelete: called\n");
	#endif

	for(i = 0; i < 128; i++) {
		if(memory[i] == p->id) {
			memory[i] = ' ';
		}
	}

	#ifdef _VISUAL_
	printf("swap out process %c\n", p->id);
	#endif
}

/*
Testing function which prints out the memory array visually.
*/
void memoryDisplay(char *memory) {
	int i,k;

	#ifdef _VERBOSE_
	printf("memoryDump: called\n");
	#endif

	for(i = 0; i < 8; i++) {
		for(k = 0; k < 16; k++) {
			printf("|%c",memory[k+(i*16)]);
		}
		printf("|\n");
	}
}

/*
Sets all characters in memory to spaces.
*/
void memoryClear(char *memory) {
	int i;

	for(i = 0; i < 128; i++) {
		memory[i] = ' ';
	}
	memory[128] = '\0';
}

/*
Returns the number of holes in memory.
*/
int memoryHoles(char *memory) {
	int i;
	int count;
	int hole;

	count = 0;
	hole = 0;

	for(i = 0; i < 128; i++) {
		if(memory[i] == ' ' && hole == 0) {
			count++;
			hole = 1;
		} else if(memory[i] != ' ' && hole == 1) {
			hole = 0;
		}
	}

	return count;
}

/*
Returns the number of processes in memory.
*/
int memoryProcesses(char *memory) {
	int i;
	int count;
	char prev;

	count = 0;
	prev = ' ';

	for(i = 0; i < 128; i++) {
		if(memory[i] != ' ' && memory[i] != prev) {
			count++;
		}
		prev = memory[i];
	}

	return count;
}

/*
Returns the percentage of memory that is full.
*/
int memoryFull(char *memory) {
	int i;
	int count;
	float result;

	count = 0;

	for(i = 0; i < 128; i++) {
		if(memory[i] != ' ') {
			count++;
		}
	}

	result = (float)count / 128.0;
	result *= 100;

	return (int)result;
}

/*
This function removes all processes from queue "q" and deallocates them.
*/
void dumpQueue(queue q) {
	process *current;

	while(fifoQ_top(q)) {
		current = (process *)fifoQ_pop(q);
		free(current);
	}
}

/*
This function reads in process information from a file "filename" and push them into a queue "q".
*/
void fillQueue(char *filename, queue q) {
	char id;
	int size;
	FILE *fp;
	process *p;
	char buffer[32];

	#ifdef _VERBOSE_
	printf("fillQueue: called\n");
	#endif

	id = '\0';
	fp = fopen(filename, "r");

	while(fgets(buffer, 32, fp) != NULL && 2 < strlen(buffer)) {
		sscanf(buffer,"%c %d",&id, &size);

		p = malloc(sizeof(process));
		p->id = id;
		p->size = size;
		p->count = 0;

		#ifdef _VERBOSE_
		printf("fillQueue: process id=%c size=%d\n", p->id, p->size);
		#endif

		fifoQ_push(q, p);
	}

	fclose(fp);

	#ifdef _VERBOSE_
	printf("fillQueue: ending\n");
	#endif

}


