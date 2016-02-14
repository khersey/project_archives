/*	Name:		newton.c
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		September 15, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "newton.h"
#include "ackermann.h"


void newton(void) {
	double x, e, resultTime;
	clock_t start, end;

	/* get input for variables */
	printf("Find the square root of number\n");
	x = getValidDouble();
	printf("Input accuracy\n");
	e = getValidDouble();

	/* do recursive method */
	printf("Recursive Result:\n");
	start = clock();
	recursiveSquareRoot(x,e,(x/2));
	end = clock();
	resultTime = (double)(end - start);
	printf("Time Taken = %f\n",resultTime);

	/* do iterative method */
	printf("Iterative Result:\n");
	start = clock();
	iterativeSquareRoot(x,e,(x/2));
	end = clock();
	resultTime = (double)(end - start);
	printf("Time Taken = %f\n",resultTime);
}

void recursiveSquareRoot(double x, double e, double a) {
	if(absoluteValue(a*a-x) <= e) {
		printf("SQRT(%f) = %f\n",x,a);
	} else {
		a = (a+x/a)/2;
		recursiveSquareRoot(x,e,a);
	}
}

void iterativeSquareRoot(double x, double e, double a) {
	while(absoluteValue(a*a-x) > e) {
		a = (a+x/a)/2;
	}
	printf("SQRT(%f) = %f\n",x,a);
}

double getValidDouble(void) {
	char c = ' ';
	double n = 0;
	do {
		printf(">");
		scanf("%lf%c", &n, &c);
		if ( c != '\n' || n <= 0) {
			printf("Warning Invalid Input!\n");
			clearBuffer();
		}
	} while( c != '\n' || n <= 0);

	return n;
}

double absoluteValue(double input) {
	if (input < 0) {
		input = input * (-1);
	}
	return input;
}

