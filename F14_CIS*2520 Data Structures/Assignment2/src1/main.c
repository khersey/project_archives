/*	Name:		main.c
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
#include "carList.h"
#include "menu.h"
#include "fileStuff.h"

int main(void) {
	int choice;
	car* availableList = NULL, * rentedList = NULL, * repairList = NULL;
	double total = 0.0;

	listFromFile("data/AvailableList.cfg",1,&availableList);
	listFromFile("data/RentedList.cfg",2,&rentedList);
	listFromFile("data/RepairList.cfg",0,&repairList);
	printf("Lists Load Complete\n");

	do {
		choice = menu();
		total += executeChoice(choice, &availableList, &rentedList, &repairList);
	} while(choice != 7);

	printf("Total Income: %.2f\n",total);

	fileFromList("data/AvailableList.cfg",&availableList);
	fileFromList("data/RentedList.cfg",&rentedList);
	fileFromList("data/RepairList.cfg",&repairList);
	printf("Lists Save Complete\n");
	printf("Exiting...\n");
 
	return 0;
}

