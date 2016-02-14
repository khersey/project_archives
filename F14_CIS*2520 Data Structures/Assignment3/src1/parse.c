/*	Name:		parse.c
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
#include "parse.h"
#include "utility.h"
#include "tree.h"

int getNextPos(int pos, char * inStr) {
	char c;
	int length = strlen(inStr);

	while(pos < length) {
		c = inStr[pos];

		if (c == ',') {
			break;
		} else if (isdigit(c) || c == '.') {
			pos++;
		} else {
			break;
		}
	}

	return pos;
}

double getNumber(int start, int end, char * inStr) {
	double output;
	int i;
	int length = end - start;
	char * temp = malloc(length + 1);
	int isDouble = 0;

	for(i = start; i < end; i++) {
		temp[i - start] = inStr[i];
		if(temp[i - start] == '.') {
			isDouble = 1;
		}
	}
	temp[length] = '\0';

	sscanf(temp, "%lf", &output);

	if(isDouble == 0) {
		i = (int)output;
		output = (double)i;
	}

	free(temp);
	return output;
}






