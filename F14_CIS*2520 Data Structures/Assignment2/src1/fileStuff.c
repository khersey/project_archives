/*	Name:		fileStuff.c
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
#include "carList.h"
#include "fileStuff.h"

void listFromFile(char* fileName, int mode, car ** top) { /* mode == 1 for order by mileage, mode == 2 for order by date or mode == 0 for push */
	int mileage, year, month, day;
	char buffer[256], tempPlate[128];
	char* plate;
	car* current;
	FILE *file;

	file = fopen(fileName,"r");

	while(fgets(buffer,sizeof(buffer),file)) {
		if(strlen(buffer) > 10){
			buffer[strcspn(buffer,"\n")] = '\0';
			sscanf(buffer, "%d %d %d %d %s", &mileage, &year, &month, &day, tempPlate);
			plate = malloc(strlen(tempPlate) + 1);
			strcpy(plate,tempPlate);
			constructCar(&current, mileage, plate, year, month, day);
			if(mode == 1) {
				insertOrderedByMileage(top,&current);
			} else if (mode == 2) {
				insertOrderedByDate(top,&current);
			} else {
				insertToFront(top,&current);
			}
		} else {
			continue;
		}
		
	}

	fclose(file);
}

void fileFromList(char* fileName, car** top) {
	FILE * file;
	car * current = *top, * destroyMe = NULL;

	file = fopen(fileName,"w");
	
	while(current != NULL) {
		fprintf(file, "%d %d %d %d %s\n", current->mileage, current->year, current->month, current->day, current->plate);
		destroyMe = current;
		current = current->next;
		destroyCar(&destroyMe);
	}

	fclose(file);

}




