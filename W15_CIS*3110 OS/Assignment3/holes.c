/* filename:   holes.c
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 3
 *
 * Main and core functions of memory management simulation.
 */


#include "holes.h"


int main(int argc, char *argv[]) {
	int i;
	char *memory;
	char *filename;
	queue inQ = NULL;
	queue swapQ = NULL;

	if(argc < 2) {
		printf("Please invoke this program with one parameter:\n");
		printf("./holes [filename]\n");
		exit(-1);
	}

	memory = malloc(sizeof(char) * 129);
	inQ = fifoQ_init();
	swapQ = fifoQ_init();

	filename = argv[1];

	for(i = 0; i < 4; i++) {
		memoryClear(memory);
		fillQueue(filename, inQ);

		runMemSim(memory, inQ, swapQ, i);

		dumpQueue(swapQ);
	}

	free(inQ);
	free(swapQ);

	return 0;
}

/*
This function runs each memory allocation algorithm, manages related statistics and prints output.
*/
void runMemSim(char *memory, queue inQ, queue swapQ, int mode) {
	int pos, lastPos;
	process *current;
	int memHoles, totalHoles;
	int memProcesses, totalProcesses;
	int memFull, totalFull;
	int loads;

	lastPos = 0;
	totalHoles = 0;
	totalProcesses = 0;
	totalFull = 0;
	loads = 0;
	
	#ifdef _VERBOSE_
	printf("runMemSim: called\n");
	#endif

	switch(mode) {
		case 0 :
			printf("-==============================-\n");
			printf("            First Fit           \n");
			printf("-==============================-\n");
			break;
		case 1 :
			printf("-==============================-\n");
			printf("            Best Fit            \n");
			printf("-==============================-\n");
			break;
		case 2 :
			printf("-==============================-\n");
			printf("            Next Fit            \n");
			printf("-==============================-\n");
			break;
		case 3 :
			printf("-==============================-\n");
			printf("            Worst Fit           \n");
			printf("-==============================-\n");
			break;
	}

	while(fifoQ_top(inQ)) {
		current = (process *)fifoQ_pop(inQ);

		switch(mode) {
			case 0 :
				pos = firstFit(memory, current->size);
				break;
			case 1 :
				pos = bestFit(memory, current->size);
				break;
			case 2 :
				pos = nextFit(memory, current->size, lastPos);
				break;
			case 3 :
				pos = worstFit(memory, current->size);
				break;
		}

		while(pos == -1) {
			memorySwap(memory, inQ, swapQ);

			switch(mode) {
				case 0 :
					pos = firstFit(memory, current->size);
					break;
				case 1 :
					pos = bestFit(memory, current->size);
					break;
				case 2 :
					pos = nextFit(memory, current->size, lastPos);
					break;
				case 3 :
					pos = worstFit(memory, current->size);
					break;
			}
		}

		lastPos = pos + current->size;
		memoryInsert(memory, pos, current);
		fifoQ_push(swapQ, current);

		loads++;
		memHoles = memoryHoles(memory);
		totalHoles += memHoles;
		memProcesses = memoryProcesses(memory);
		totalProcesses += memProcesses;
		memFull = memoryFull(memory);
		totalFull += memFull;

		printf("Process %c Loaded, Processes=%d, Holes=%d, Memusage=%d%%, Average Memusage=%d%%\n", current->id, memProcesses, memHoles, memFull, (int) ((float)totalFull/(float)loads));

		#ifdef _VISUAL_
		memoryDisplay(memory);
		printf("\n");
		#endif
	}

	printf("Total Loads=%d, Average Processes=%.1f, Average Holes=%.1f, Average Memusage=%d%%\n\n", loads, (float)totalProcesses/(float)loads, (float)totalHoles/(float)loads, (int) ((float)totalFull/(float)loads));

}

/*
Returns either the index of the first available hole of size "size" 
or returns -1 if no holes large enough exist.
*/
int firstFit(char *memory, int size) {
	int i;
	int holeSize;
	int holeStart;
	char prev;

	holeSize = 0;
	prev = '_';
	holeStart = 0;

	#ifdef _VERBOSE_
	printf("findFirst: called\n");
	#endif

	for(i = 0; i < 128; i++) {
		
		if(memory[i] == ' ' && prev != ' ') {
			holeSize++;
			holeStart = i;
		} else if(memory[i] == ' ' && prev == ' ') {
			holeSize++;
		} else {
			holeSize = 0;
		} 

		#ifdef _VERBOSE_
		printf("findFirst: memory[%d]=\"%c\" holeSize=%d holeStart=%d\n",i ,memory[i], holeSize, holeStart);
		#endif

		if(holeSize >= size) {
			return holeStart;
		}

		prev = memory[i];
	}

	return -1;
}

/*
Returns either the index of the available hole of "size" 
or returns -1 if no holes large enough exist.
*/
int bestFit(char *memory, int size) {
	int i;
	int holeSize,  bestSize;
	int holeStart, bestStart;
	char prev;

	holeSize = 0;
	bestSize = 129;
	holeStart = 0;
	bestStart = -1;
	prev = '_';

	#ifdef _VERBOSE_
	printf("bestFit: called\n");
	#endif

	for(i = 0; i < 128; i++) {
		
		if(memory[i] == ' ' && prev != ' ') {
			holeSize++;
			holeStart = i;
		} else if(memory[i] == ' ' && prev == ' ') {
			holeSize++;
			if(holeSize >= size && holeSize < bestSize && i == 127) {
				bestSize = holeSize;
				bestStart = holeStart;
			}
		} else if(memory[i] != ' ' && prev == ' ') {
			if(holeSize >= size && holeSize < bestSize) {
				bestSize = holeSize;
				bestStart = holeStart;
			}

			holeSize = 0;
		}

		#ifdef _VERBOSE_
		printf("bestFit: memory[%d]=\"%c\" holeSize=%d holeStart=%d\n",i ,memory[i], holeSize, holeStart);
		#endif

		prev = memory[i];
	}

	return bestStart;
}

/*
Returns either the index of the available hole of "size" 
or returns -1 if no holes large enough exist.
*/
int nextFit(char *memory, int size, int location) {
	int i;
	int holeSize;
	int holeStart;
	char prev;

	holeSize = 0;
	prev = '_';
	holeStart = 0;

	#ifdef _VERBOSE_
	printf("nextFit: called\n");
	#endif

	if(127-location < size) {
		location = 0;
	}

	for(i = location; i < 128; i++) {
		
		if(memory[i] == ' ' && prev != ' ') {
			holeSize++;
			holeStart = i;
		} else if(memory[i] == ' ' && prev == ' ') {
			holeSize++;
		} else {
			holeSize = 0;
		} 

		#ifdef _VERBOSE_
		printf("nextFit: memory[%d]=\"%c\" holeSize=%d holeStart=%d\n",i ,memory[i], holeSize, holeStart);
		#endif

		if(holeSize >= size) {
			return holeStart;
		}

		prev = memory[i];
	}

	return -1;
}

/*
Returns either the index of the available hole of "size" 
or returns -1 if no holes large enough exist.
*/
int worstFit(char *memory, int size) {
	int i;
	int holeSize,  bestSize;
	int holeStart, bestStart;
	char prev;

	holeSize = 0;
	bestSize = -1;
	holeStart = 0;
	bestStart = -1;
	prev = '_';

	#ifdef _VERBOSE_
	printf("worstFit: called\n");
	#endif

	for(i = 0; i < 128; i++) {
		
		if(memory[i] == ' ' && prev != ' ') {
			holeSize++;
			holeStart = i;
		} else if(memory[i] == ' ' && prev == ' ') {
			holeSize++;
			if(holeSize >= size && holeSize > bestSize && i == 127) {
				bestSize = holeSize;
				bestStart = holeStart;
			}
		} else if(memory[i] != ' ' && prev == ' ') {
			if(holeSize >= size && holeSize > bestSize) {
				bestSize = holeSize;
				bestStart = holeStart;
			}

			holeSize = 0;
		}

		#ifdef _VERBOSE_
		printf("worstFit: memory[%d]=\"%c\" holeSize=%d holeStart=%d\n",i ,memory[i], holeSize, holeStart);
		#endif

		prev = memory[i];
	}

	return bestStart;
}

