/*	Name:		postfix.h
 *  Assignment 2: Part 2
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */

#ifndef POSTFIX_H_INCLUDED
#define POSTFIX_H_INCLUDED

/**************************
**	struct declarations	 **
**************************/

/*
Node from implementing a linked list stack.
int value contains a numeric value between 0-9.
node* next points to the next element in the list 
or NULL if there is no next element.
*/
typedef struct node node;
struct node {
	int value;
	node* next;
};

/*****************************
**	function declarations	**
*****************************/

/*
Implements the push method as seen in lecture slides c05-f14.
Adds an element to the top of the stack.
*/
void push(node** top, int value);

/*
Implements the pop method as seen in lecture slides c05-f14
Revomes an element from the top of the stack and returns it.
*/
int pop(node** top);

/* 
Loops through the postfix function, passed in from the terminal, one character at a time.
If a character is a number it is pushed to the top of the stack.
If a character is an operator, the last two numbers are popped out of the stack, and passed to 
numberCrunkcher().  The result returned will be then pushed to the stack.
When all characters have been looped through the only value left in the stack will be the final result.
This final value is popped and returned.
*/
int postfix(node** top, char* inputStr);

/*
This function takes two numbers and a mathematical operation and executes this operation on the two 
numbers and returns the result. Defensively progammed to account for division by zero.
*/
int numberCruncher(int num1, int num2, char op);

/*
This function systematically frees every element in the linked list.
*/
void destroyList(node** top);

#endif


