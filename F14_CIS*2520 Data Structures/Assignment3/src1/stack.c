/*	Name:		stack.c
 *  Assignment 3: Part 1
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"


void push (node** top, leaf ** value) {
	node * new = malloc(sizeof(node));
	if (!new) exit(-1);
	new->value = *value;
	new->next = *top;
	*top = new;
}

leaf * pop(node** top) {
	leaf * value;
	node* temp;
	if (!(*top)) return -1;
	temp = *top;
	*top = temp->next;
	value = temp->value;
	free(temp);
	return value;
}

void printStack(node ** top) {
	node * current = *top;
	while(current) {
		printLeaf(current->value);
		current = current->next;
	}
}

