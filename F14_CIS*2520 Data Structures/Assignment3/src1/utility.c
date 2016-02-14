/*	Name:		utility.c
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
#include "utility.h"

int menu(void) {
	char result;
	char c;
	int output = 0;

	printf("\n1. Display\n");
	printf("2. Preorder\n");
	printf("3. Inorder\n");
	printf("4. Postorder\n");
	printf("5. Update\n");
	printf("6. Calculate\n");
	printf("7. Exit\n");

	do {
		printf(">");
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

int isOp(char c) {
	if(c == '(' || c == '*' || c == '-' || c == '+' || c == '/') {
		return 1;
	} else {
		return 0;
	}
}

void death(int code) {
	if(code == -1) {
		printf("Something went horribly wrong while allocating memory\n");
	} else if(code == 0) {
		printf("Something went horribly wrong when you killed everyone dividing by zero\n");
	}else if(code == 1) {
		printf("Something went horribly wrong while processing user input\n");
	} else if(code == 2) {
		printf("Something went horribly wrong building your binary tree\n");
	} else if(code == 3) {
		printf("Something went horribly wrong popping from the stack\n");
	}

	printf("The program will now quit....\n");
	exit(-1);
}


