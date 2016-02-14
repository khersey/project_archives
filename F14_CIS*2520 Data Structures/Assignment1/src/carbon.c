/*	Name:		carbon.c
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		September 15, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carbon.h"

void carbon(void) {
	char c;
	char * carbonStr = malloc(sizeof(char) * (strlen("carbon")+1));
	strcpy(carbonStr,"carbon");

	printf("Press Enter to Continue\n>");
	scanf("%c",&c);

	generateVariant(carbonStr,0);

	free (carbonStr);
}

void generateVariant(char * inString, int pos) {
	int i, length;
	length = strlen(inString);

	if (pos<length) {

		for (i = pos; i < length; i++) {
			swapChar(&inString[i],&inString[pos]);
			generateVariant(inString,pos+1);
			swapChar(&inString[i],&inString[pos]);
		}

	} else {

		printf("%s\n",inString);

	}
	
}

void swapChar(char * first, char * second) {
	char temp = *first;
	*first = *second;
	*second = temp;
}
