/* filename:   priorityQueue.c
 * author:     Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 2
 *
 * This file contains functions implementing a priority queue.
 *
 * Worked Cited: rosettacode.org/wiki/Priority_queue
 */

#include "priorityQueue.h"


pQueue pQueue_init(int size) {
	if (size < 4) size = 4;

	pQueue pq = malloc(sizeof(priorityQueue));
	pq->elements = malloc(sizeof(pQ_element) * size);
	pq->allocated = size;
	pq->used = 1;

	return pq;
}

void pQueue_push(pQueue pq, void * data, int key) {
	pQ_element *elements;
	int n, m;

	if(pq->used >= pq->allocated) {
		pq->allocated *= 2;
		elements = pq->elements = realloc(pq->elements, sizeof(pQ_element) * pq->allocated);
	} else {
		elements = pq->elements;
	}

	n = pq->used++;

	while((m = n / 2) && key < elements[m].key) {
		elements[n] = elements[m];
		n = m;
	}
	elements[n].data = data;
	elements[n].key = key;
}

void * pQueue_pop(pQueue pq, int *key) {
	void * out;
	int n, m;
	pQ_element *elements;

	if (pq->used == 1) {
		return NULL;
	}

	elements = pq->elements;
	out = elements[1].data;
	if(key) {
		*key = elements[1].key;
	}

	--pq->used;

	n = 1;
	while((m = n * 2) < pq->used) {
		if (m + 1 < pq->used && elements[m].key > elements[m+1].key) {
			m++;
		}
		if (elements[pq->used].key <= elements[m].key) {
			break;
		}
		elements[n] = elements[m];
		n = m;
	}

	elements[n] = elements[pq->used];
	
	if (pq->used < pq->allocated / 2 && pq->used >= 16) {
		pq->elements = realloc(pq->elements,(pq->allocated /= 2) * sizeof(pQ_element));
	}

	return out;
}

void * pQueue_top(pQueue pq, int *key) {
	if (pq->used == 1) {
		return NULL;
	}
	if (key) {
		*key = pq->elements[1].key;
	} 
	return pq->elements[1].data;
}



