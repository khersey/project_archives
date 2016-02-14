/* filename:   fifoQueue.h
 * author:     Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 2
 *
 * This file contains function declarations for implementing a queue
 * as well as types necesary for implementing it.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct qNode qNode;
struct qNode {
	void * data;
	qNode * next;
};

typedef struct fifoQueue fifoQueue;
struct fifoQueue
{
	qNode * head;
	qNode * tail;
};

typedef fifoQueue* queue;


queue fifoQ_init(void); 

void fifoQ_push(queue fq, void * data);

void * fifoQ_pop(queue fq);

void * fifoQ_top(queue fq);
