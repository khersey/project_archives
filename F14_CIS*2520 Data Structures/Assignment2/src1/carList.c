/*	Name:		carList.c
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
#include "utility.h"
#include "menu.h"

void constructCar(car** newCar, int mileage, char* plate, int year, int month, int day) {
	*newCar = malloc(sizeof(car));
	if(!(*newCar)) exit(-1);
	(*newCar)->plate = malloc(strlen(plate) + 1);
	strcpy((*newCar)->plate, plate);
	free(plate);
	(*newCar)->mileage = mileage;
	(*newCar)->year = year;
	(*newCar)->month = month;
	(*newCar)->day = day;
	(*newCar)->next = NULL;
}

int equals(car** first, car** second) {
	if ((*first)->mileage == (*second)->mileage && strcmp((*first)->plate,(*second)->plate) == 0 && (*first)->year == (*second)->year 
		&& (*first)->month == (*second)->month && (*first)->day == (*second)->day) {
		return 0;
	} else {
		return 1;
	}
}

int dateCompare(car** first, car** second) { 
	if ((*first)->year == (*second)->year) {
		if ((*first)->month == (*second)->month) {
			if((*first)->day == (*second)->day) {
				return 0;
			} else if ((*first)->day > (*second)->day){
				return 1;
			} else {
				return -1;
			}
		} else if ((*first)->month > (*second)->month) {
			return 1;
		} else {
			return -1;
		}
	} else if ((*first)->year > (*second)->year) {
		return 1;
	} else {
		return -1;
	}
}

void destroyList(car** top) {
	car *next, *destroy;
	destroy = *top;
	while(destroy != NULL) {
		next=destroy->next;
		free(destroy->plate);
		free(destroy);
		destroy = next;
	}
	*top = NULL;
}

void destroyCar(car** someCar) {
	free((*someCar)->plate);
	free(*someCar);
}

void insertOrderedByMileage(car** top, car** newCar) {
	car* current = *top;

	if (current == NULL) { 		/* list is empty */
		*top = *newCar;
	} else if ((*top)->mileage > (*newCar)->mileage) {  /* insert to front of list */
		(*newCar)->next = current;
		*top = *newCar;
	} else {
		while (current != NULL) {
			if (current->next == NULL) {	/* insert to the end of the list */
				current->next = *newCar;
				break;
			} else if (current->mileage < (*newCar)->mileage && current->next->mileage < (*newCar)->mileage) { /* next node */
				current = current->next;
			} else if (current->mileage < (*newCar)->mileage && current->next->mileage >= (*newCar)->mileage) { /* insert after current */
				(*newCar)->next = current->next;
				current->next = *newCar;
				break;
			} else {
				printf("something went wrong INSERTING into an ordered by mileage list\n"); 
			}
		}
		
	}
}

void insertToFront(car** top, car** newCar) {
	car* current = *top;
	if(current == NULL) {
		*top = *newCar;
		(*newCar)->next = NULL;
	} else {
		(*newCar)->next = current;
		*top = *newCar;
	}
}

void insertOrderedByDate(car** top, car** newCar) {
	car* current = *top;

	if(current == NULL) { 		/* list is empty */
		*top = *newCar;
	} else if (dateCompare(newCar,top) <= 0){
		(*newCar)->next = current;
		*top = *newCar;
	} else {
		while(current != NULL) {
			if (current->next == NULL) {	/* insert to the end of the list */
				current->next = *newCar;
				break;
			} else if (dateCompare(newCar,&current) > 0 && dateCompare(newCar,&current->next) > 0) { /* next node */
				current = current->next;
			} else if (dateCompare(newCar,&current) > 0 && dateCompare(newCar,&current->next) <= 0) { /* insert after current */
				(*newCar)->next = current->next;
				*top = *newCar;
				break;
			} else {
				printf("ERROR: something went wrong INSERTING into an ordered by date list\n");
			}

		}
	}
}

void pop(car** top, car** current) {
	*current = *top;

	if(current != NULL) {
		*top = (*current)->next;
	}

	(*current)->next = NULL;

}

void printList(car** top) {
	car * current = *top;
	while(current != NULL) {
		printCar(&current);
		current = current->next;
	}
}

void printCar(car** element) {
	if((*element)->year == 0 && (*element)->month == 0 && (*element)->day == 0) {
		printf("Plate: %s\nMileage: %d\n", (*element)->plate, (*element)->mileage);
	} else {
		printf("Plate: %s\nMileage: %d\nExpected Return Date: %02d/%02d/%02d (yy/mm/dd)\n", 
			(*element)->plate, (*element)->mileage, (*element)->year, (*element)->month, (*element)->day);
	}
}

void extractFromList(car** top, char* plate, car** current) {
	car* last;

	*current = *top;

	while(*current != NULL) {
		if(strcmp((*current)->plate, plate) == 0) {
			break;
		} else {
			last = *current;
			*current = (*current)->next;
		}
	}

	if(*current != NULL) {
		if(*current == *top) {
			*top = (*current)->next;
		} else {
			last->next = (*current)->next;
		}

		(*current)->next = NULL;
	} else {
		printf("ERROR: could not find a car matching that plate\n");
		*current = NULL;
	}

}








