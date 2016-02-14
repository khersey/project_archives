/*	Name:		utility.c
 *  Assignment 4
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 20, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utility.h"

void death(int errorCode, const char *errorMessage) {
	if (errorCode == -1) {
		printf("Memory Allocation Failed for %s\n",errorMessage);
	} else if (errorCode == -2) {
		printf("NULL value error %s\n",errorMessage);
	}

	exit(-1);
}

char * getString(void) {
    char buffer[128];
    char *outStr;

    scanf("%s",buffer);

    outStr = malloc(strlen(buffer) + 1);
    strcpy(outStr,buffer);
    return outStr;
}

int getInt(void) {
    char *temp;
    int output;

    temp = getString();
    output = atoi(temp);
    free(temp);

    return output;
}


int menu(void) {
	char result;
	char c;
	int output = 0;

	printf("1. Initialization\n");
	printf("2. Find\n");
	printf("3. Insert\n");
	printf("4. Remove\n");
	printf("5. Check Height and Size\n");
	printf("6. Find All (above a given frequency)\n");
	printf("7. Exit\n");

	do {
		printf("avl/> ");
		clearBuffer();
		result = getchar();
		c = result;
		while(c != '\n') {
			c = getchar();
		}

		if (!(isdigit(result))) {
			printf("please input a valid integer\n");
		}
		if (isdigit(result) && ((result-'0') > 7 || (result-'0') == 0)) {
			printf("Please input a valid integer (range 1-7)\n");
		} else {
			output = result - '0';
		}

	} while(output == 0);

	return output;
}

void clearBuffer(void) {
	fseek(stdin,0,SEEK_END);
}

int max(int x, int y) {
	if (x >= y) {
		return x;
	} else {
		return y;
	}
}


