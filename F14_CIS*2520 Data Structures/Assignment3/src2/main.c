/*	Name:		main.c
 *  Assignment 3: Part 2
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 01, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include "filestuff.h"
#include "arraystuff.h"

int main(void) {
	int arr[20][10];

	loadArray(arr);

	printf("\nORIGINAL DATA:\n");
	printArray(arr);

	sortHeap(arr);

	printf("\nAFTER HEAP SORT:\n");
	printArray(arr);
	printf("\n");

	return 0;
}


