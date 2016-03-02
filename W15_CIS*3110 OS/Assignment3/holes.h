/* filename:   holes.h
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 3
 *
 * Function and structure declarations for memory management simulation.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fifoQueue.h"


typedef struct process process;
struct process {
	char id;
	int size;
	int count;
};


/*********************
holes.c 
*********************/

void runMemSim(char *memory, queue inQ, queue swapQ, int mode) ;

int firstFit(char *memory, int size);

int bestFit(char *memory, int size);

int nextFit(char *memory, int size, int location);

int worstFit(char *memory, int size);


/*********************
memUtils.c
*********************/

void memorySwap(char *memory, queue inQ, queue swapQ);

void memoryInsert(char *memory, int location, process *p);

void memoryDelete(char *memory, process *p);

void memoryDisplay(char *memory);

void memoryClear(char *memory);

int memoryHoles(char *memory);

int memoryProcesses(char *memory);

int memoryFull(char *memory);

void dumpQueue(queue q);

void fillQueue(char *filename, queue q);

