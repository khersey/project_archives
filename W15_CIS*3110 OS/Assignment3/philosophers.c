/* filename:   philosophers.c
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 3
 *
 * Solution to the dining philosopher's problem.
 * My program avoids deadlock by only allowing [number of philosophers] - 1
 * to pick up forks at any one time.
 */

#include "philosophers.h"

int main(int argc, char *argv[]) {
	int pCount;
	int eCount;

	if(argc < 3) {
		printf("This program requires 2 parameters\n");
		printf("Please invoke with:\n ./executable [number of philosophers] [number of times to eat]\n ");
		exit(-1);
	}

	pCount = atoi(argv[1]);
	eCount = atoi(argv[2]);

	if(pCount < 2) {
		printf("ERROR: Number of Philosophers must be atleast 2\n");
		exit(-1);
	}

	if(eCount < 1 || eCount > 1000) {
		printf("ERROR: Number of times to eat must be within 1 and 1000\n");
		exit(-1);
	}

	run(pCount, eCount);

	return 0;
}

/*
Operations to be performed by each thread.
void *p will be a param *
*/
void *doThreadStuff(void *p) {
	int i;
	param * data = (param *)p;

	for(i = 0; i < data->eCount; i++) {
		printf("Philosopher %d thinking...\n", data->id);
		sem_wait(data->lock);
		sem_wait(&data->forks[data->id]);
		sem_wait(&data->forks[(data->id+1) % data->pCount]);
		printf("Philosopher %d eating...\n", data->id);
		sem_post(&data->forks[data->id]);
		sem_post(&data->forks[(data->id+1) % data->pCount]);
		sem_post(data->lock);
	}

	printf("Philosopher %d thinking...\n", data->id);
	free(data);
	pthread_exit(NULL);
}

/*
This function initializes the Semaphores and Threads.  Also allocates memory for thread parameters.
*/
void run(int philoCount, int eatCount) {
	int i;
	param *argument;
	pthread_t philosophers[philoCount];
	sem_t forks[philoCount];
	sem_t lock;

	for(i = 0; i < philoCount; i++) {
		sem_init(&forks[i], 0, 1);
	}
	sem_init(&lock, 0, philoCount - 1);

	for(i = 0; i < philoCount; i++) {
		argument = malloc(sizeof(param));
		argument->id = i;
		argument->pCount = philoCount;
		argument->eCount = eatCount;
		argument->forks = forks;
		argument->lock = &lock;

		pthread_create(&philosophers[i], NULL, doThreadStuff, (void*)argument);
	}

	for(i = 0; i < philoCount; i++) {
		pthread_join(philosophers[i], NULL);
	}
}
