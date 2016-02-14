/*	Name:		fileStuff.h
 *  Assignment 4
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 20, 2014
 *  
 */

#ifndef FILE_STUFF_H_INCLUDED
#define FILE_STUFF_H_INCLUDED


typedef struct stack stack;
struct stack {
	char *key;
	stack *next;
};


void readFromFile(stack **root);

void push (stack **root, char *key);

char * pop(stack **root);


#endif

