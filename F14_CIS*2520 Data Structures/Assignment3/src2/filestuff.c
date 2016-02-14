/*	Name:		filestuff.c
 *  Assignment 3: Part 2
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
#include "filestuff.h"

void loadArray(int arr[20][10] ) {
	int i, j, index;
	FILE *file;
	char buffer[128];

	file = fopen("f.dat", "r");

	for(i = 0; i<20; i++) {
		fgets(buffer,sizeof(buffer),file);
		buffer[strcspn(buffer,"\n")] = '\0';
		index = 0;
		for(j = 0;j<10; j++) {
			arr[i][j] = getNextInt(index,buffer);
			index += 3;
		}
	}

	fclose(file); 
	
}

int getNextInt(int index, char inStr[128]) {
	char temp[4];
	int output;
	output = 0;

	temp[0] = inStr[index];
	temp[1] = inStr[index+1];
	temp[2] = inStr[index+2];
	temp[3] = '\0';

	sscanf(temp, "%d", &output);

	return output;
}



