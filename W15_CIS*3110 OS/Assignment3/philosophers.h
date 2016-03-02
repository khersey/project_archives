/* filename:   philosophers.h
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 3
 *
 * Solution to the dining philosopher's problem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


#ifndef PHILOSOPHERS_H_INCLUDE
#define PHILOSOPHERS_H_INCLUDE


typedef struct param param;
struct param
{
	int id;
	int pCount;
	int eCount;
	sem_t *forks;
	sem_t *lock;
};


void run(int philoCount, int eatCount) ;


void *doThreadStuff(void *p) ;


#endif
