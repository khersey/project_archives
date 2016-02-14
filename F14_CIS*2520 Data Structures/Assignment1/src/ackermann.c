/*	Name:		ackermann.c
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		September 15, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ackermann.h"


void ackermann(void) {
	int m, n, output, nMaxSize;

	printf("Please input first integer (0-4)\n");
	m = getIntInput(4);

	/*  These are the max values of n per m value that will run without the crashing the program 
		found through trial and error	*/
	if (m == 4) {
		nMaxSize = 1;
	} else if (m == 3) {
		nMaxSize = 13;
	} else if (m == 2) {
		nMaxSize = 87350;
	} else {
		nMaxSize = 160000;
	}

	printf("Please input second integer (0-%i)\n",nMaxSize);
	n = getIntInput(nMaxSize);

	output = runAckermann(m,n);

	printf("Output: %i\n", output);
}

int getIntInput(int maxSize) {
	char c = ' ';
	int n = -1;
	do {
		printf(">");
		scanf("%d%c", &n, &c) ;
		if ( c != '\n' || n < 0) {
			printf("Warning Invalid Input!\n");
			clearBuffer();
		}
	} while( c != '\n' || n < 0);

	return n;
}

int runAckermann(int m, int n) {
	int result = 0;
	if (m == 0 && n >= 0) {
		return n + 1;
	} else if (n == 0 && m > 0) {
		return runAckermann(m-1,1);
	} else if (m > 0 && n > 0) {
		return runAckermann(m-1,runAckermann(m,n-1));
	} else {
		printf("Invalid Input: M=%i  N=%i \n", m, n);
	}
	return result;
}

void clearBuffer(void) {
	char c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}


