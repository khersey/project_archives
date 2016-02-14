/* filename:   fifoQueue.c
 * author:     Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 2
 *
 * This file contains functions for implementing a simple linked list FIFO queue.
 */

#include "fifoQueue.h"

queue fifoQ_init(void) {
	queue fq = malloc(sizeof(fifoQueue));
	fq->head = NULL;
	fq->tail = NULL;
	return fq;
}

void fifoQ_push(queue fq, void * data) {
	qNode * node;
	node = malloc(sizeof(qNode));
	node->data = data;
	node->next = NULL;


	if(fq->head == NULL) {
		fq->head = node;
		fq->tail = node;
	} else {
		fq->tail->next = node;
		fq->tail = node;

	}
}

void * fifoQ_pop(queue fq) {
	void * out;
	qNode * temp;
	if(fq->head == NULL) return NULL;

	out = fq->head->data;

	temp = fq->head;

	fq->head = fq->head->next;

	/* tail could be hanging pointer */
	if(fq->head == NULL) fq->tail = NULL;

	free(temp);

	return out;

}

void * fifoQ_top(queue fq) {
	if(fq->head == NULL) return NULL;
	return fq->head->data;
}

