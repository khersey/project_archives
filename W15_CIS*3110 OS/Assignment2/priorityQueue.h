/* filename:   priorityQueue.h
 * author:     Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 2
 *
 * This file contains function declarations for implementing a priority queue
 * as well as types necesary for implementing it.
 *
 * Worked Cited: rosettacode.org/wiki/Priority_queue
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct pQ_element pQ_element;
typedef struct priorityQueue priorityQueue;
typedef priorityQueue* pQueue;

struct pQ_element {
	void * data;
	int key;
};

struct priorityQueue {
	pQ_element * elements;
	int used;
	int allocated;
};



pQueue pQueue_init(int size);

void pQueue_push(pQueue pq, void * data, int key);

void * pQueue_pop(pQueue pq, int *key);

void * pQueue_top(pQueue pq, int *key);

