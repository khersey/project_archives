/*	Name:		main.c
 *  Assignment 2: Part 2
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfix.h"


int main(int argc, char *argv[]) {
	node* stack;
	int result;
	result = postfix(&stack,argv[1]);
	printf("result = %d\n",result);
	destroyList(&stack);
	return 0;
}

