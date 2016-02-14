/*	Name:		main.c
 *  Assignment 3: Part 1i
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 01, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "parse.h"
#include "utility.h"

int main(int argc, char *argv[]) {
 	int choice = 0;
 	char * inStr;
 	node * opStack = NULL;
 	node * doneStack = NULL;
 	leaf * root;

 	/*
 	SAMPLES:
 	(((x1+5.12)*(x2-7.68))/x3)
 	*/
 	printf("\n\n");
 	if (argc == 2) {
 		inStr = malloc(strlen(argv[1]) + 1);
 		strcpy(inStr, argv[1]);
 	} else {
 		inStr = malloc(strlen("(((x1+5.12)*(x2-7.68))/x3)" + 1));
 		strcpy(inStr, "(((x1+5.12)*(x2-7.68))/x3)");
 		printf("NOTE: You are using the default equation\n");
 		printf("To use a custom equation, enter it as an argument\n");
 	}

 	printf("Equation: %s\n", inStr);

 	processInput(inStr,&opStack,&doneStack);
 	buildTree(&opStack,&doneStack,&root);

 	do {

 		choice = menu();

	 	if(choice == 1) {
			startDrawTree(root);
			printVarValues(root);
			printf("(Scroll Up)\n");
		} else if(choice == 2) {
			printf("\n");
			preOrderTraversal(root);
			printf("\n");
		} else if(choice == 3) {
			printf("\n");
			inOrderTraversal(root);
			printf("\n");
		} else if(choice == 4) {
			printf("\n");
			postOrderTraversal(root);
			printf("\n");
		} else if(choice == 5) {
			printf("\n");
			updateVar(&root);
			printf("\n");
		} else if(choice == 6) {
			printf("\n");
			runCalculation(&root);
			printf("\n");
		}

	} while(choice != 7);

	free(inStr);
	
 	return 0;
 	
 }
