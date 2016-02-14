/*	Name:		postfix.c
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
#include <ctype.h>
#include "postfix.h"


void push(node** top, int value) {
	node* new = malloc(sizeof(node));
	if (!new) exit(-1);
	new->value = value;
	new->next = *top;
	*top = new;
}

int pop(node** top) {
	int value;
	node* temp;
	if (!(*top)) return -1;
	temp = *top;
	*top = temp->next;
	value = temp->value;
	free(temp);
	return  value;
}

int postfix(node** top, char* inputStr) {
	int num1, num2, result, i, length;
	char c;

	length = strlen(inputStr);

	for(i = 0; i < length; i++) {
		c = inputStr[i];
		if (isdigit(c)) {
			push(top,c - '0');
		} else {
			num2 = pop(top);
			num1 = pop(top);
			result = numberCruncher(num1,num2,c);
			push(top,result);
		}
	}
	result = pop(top);
	return result;
}

int numberCruncher(int num1, int num2, char op) {
	if (op == '+') return num1 + num2;
	else if (op == '-') return num1 - num2;
	else if (op == '*') return num1 * num2;
	else if (op == '/' && num2!=0) return num1 / num2;
	else if (op == '/' && num2==0) {
		printf("DIVISION BY ZERO ERROR\n");
		return 0;
	} else {
		printf("UNKNOWN OPERATOR ERROR\n");
		return 0;
	}
}

void destroyList(node** top) {
	node *next, *destroy;
	destroy = *top;
	while(destroy != NULL) {
		next=destroy->next;
		free(destroy);
		destroy = next;
	}
	*top = NULL;
}






