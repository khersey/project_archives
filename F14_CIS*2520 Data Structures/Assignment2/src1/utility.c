/*	Name:		utility.c
 *  Assignment 2: Part 1
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

void clearBuffer(void) {
	fseek(stdin,0,SEEK_END);
}

char* getPlate(void) {
	char buffer[128];
	char * output;

	clearBuffer();
	printf("Please Enter Car Plate Number\n");
	printf(">");
	scanf("%s",buffer);
	output = malloc(strlen(buffer) + 1);
	strcpy(output, buffer);

	return output;
}

/*
NOTE TO SELF:
you need to limit month to 1-12 
and day to 1-31
*/
void getDate(int * date) { /* PASS IN AN ARRAY int date[3] = {0,0,0} */
	int i;
	char buffer[128];
	char year[3];
	char month[3];
	char day[3];

	printf("Please Enter Expected Return Date (yymmdd)\n");
	do {
		printf(">");
		clearBuffer();
		scanf("%s",buffer);
		buffer[strcspn(buffer,"\n")] = '\0';
		if(strlen(buffer) != 6) {
			printf("ERROR: input is too long.  please follow format (yymmdd)\n");
			continue;
		}
		for(i = 0; i < 6; i++) {
			if (isdigit(buffer[i])) {
				if (i>3){
					day[i-4] = buffer[i];
				} else if (i>1) {
					month[i-2] = buffer[i];
				} else {
					year[i]  = buffer [i];
				}
			} else {
				printf("ERROR: date input must be all digits\n");
				break;
			}

			if (i == 5) {
				day[2] = '\0';
				year[2] = '\0';
				month[2] = '\0';

				date[0] = atoi(year);
				date[1] = atoi(month);
				date[2] = atoi(day);
			}
		}

	} while(date[0] == 0 && date[1] == 0 && date[2] == 0);
}

int getMileage(int baseLine) {
	int mileage = -1;
	char c = '\0';

	printf("Please Enter Car Mileage\n");

	do {
		printf(">");
		clearBuffer();
		scanf("%i%c",&mileage,&c);
		if(mileage < baseLine) {
			printf("Mileage must be larger than %d\n",baseLine);
		}
		if(c != '\n') {
			printf("Input must be only digits\n");
		}
	} while (mileage < baseLine || c != '\n');

	return mileage;
}

float calculateTransaction(int startMileage, int endMileage) {
	int difference = endMileage - startMileage;
	float cost = 40.00;
	if (difference > 100) {
		difference -= 100;
		cost += (float)difference * 0.15;
	}
	return cost;
}



