/*	Name:		menu.c
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

int menu(void) {
	char c;
	int output;

	printf("\n1. Add a new car to the available-for-rent list\n");
	printf("2. Add a returned car to the available-for-rent list\n");
	printf("3. Add a returned car to the repair list\n");
	printf("4. Transfer a car from the repair list to the available-for-rent list\n");
	printf("5. Rent the first available car\n");
	printf("6. Print all lists\n");
	printf("7. Quit\n");

	do {
		printf(">");
		clearBuffer();
		c = getchar();
		if (!(isdigit(c))) {
			printf("please input a valid integer\n");
		}
		if (isdigit(c) && ((c-'0') > 7 || (c-'0') == 0)) {
			printf("Please input a valid integer (range 1-7)\n");
		}
	} while(!(isdigit(c)) && !((c-'0') < 7 ) && !((c-'0') == 0));
	output = c - '0';
	return output;
}

double executeChoice(int choice, car** availableList, car** rentedList, car** repairList) {
	double income = 0.0;
	if (choice == 1) {

		choice1(availableList);

	} else if (choice == 2) {

		income = choice2(rentedList, availableList);

	} else if (choice == 3) {

		income = choice3(rentedList, repairList);

	} else if (choice == 4) {

		choice4(repairList, availableList);

	} else if (choice == 5) {

		choice5(availableList, rentedList);

	} else if (choice == 6) {

		choice6(availableList, rentedList, repairList);

	} 

	return income;
}

void choice1(car** availableList) {
	int mileage = 0;
	car* newCar = NULL;
	char * plate;

	plate = getPlate();
	mileage = getMileage(0);

	constructCar(&newCar, mileage, plate, 0, 0, 0);

	insertOrderedByMileage(availableList, &newCar);
	printf("\nNew Car with plate: %s added to availableList\n",newCar->plate);

}

double choice2(car** rentedList, car** availableList) {
	int mileage = 0;
	char * plate;
	car* returnedCar = NULL;
	double cost = 0.0;

	plate = getPlate();
	extractFromList(rentedList, plate, &returnedCar);
	if (returnedCar != NULL) {
		mileage = getMileage(returnedCar->mileage);

		returnedCar->next = NULL;

		returnedCar->year = 0;
		returnedCar->month = 0;
		returnedCar->day = 0;
		cost = calculateTransaction(returnedCar->mileage, mileage);
		returnedCar->mileage = mileage;
		printf("\nThe cost of your trip is $%.2f\n",cost);
		insertOrderedByMileage(availableList, &returnedCar);
		printf("Car with plate: %s moved to availableList\n",returnedCar->plate);
		
	}

	return cost;
}

double choice3(car** rentedList, car** repairList) {
	int mileage = 0;
	char * plate;
	car* returnedCar = NULL;
	double cost = 0.0;

	plate = getPlate();

	extractFromList(rentedList, plate, &returnedCar);
	if (returnedCar != NULL) {
		returnedCar->next = NULL;

		mileage = getMileage(returnedCar->mileage);

		if (returnedCar == NULL) {
			printf("There was no car found with that license plate in the rented car list\n");
		} else {
			returnedCar->year = 0;
			returnedCar->month = 0;
			returnedCar->day = 0;
			cost = calculateTransaction(returnedCar->mileage, mileage);
			returnedCar->mileage = mileage;
			printf("\nThe cost of your trip is $%.2f\n",cost);
			insertToFront(repairList, &returnedCar);
			printf("Car with plate: %s moved to repairList\n",returnedCar->plate);
		}
	}
	
	return cost;

}

void choice4(car** repairList, car** availableList) {
	char * plate;
	car * returnedCar = NULL;

	plate = getPlate();

	extractFromList(repairList, plate, &returnedCar);

	if (returnedCar == NULL) {
		/* There was a print statement here but I didnt need it... */
	} else {
		insertOrderedByMileage(availableList, &returnedCar);
		printf("\nCar with plate: %s moved to availableList\n",returnedCar->plate);
	}
}

void choice5(car** availableList, car** rentedList) {
	int date[3] = {0,0,0};
	car * firstCar;

	getDate(date);

	if (date[1] > 0 && date[1] < 13 && date[2] > 0 && date[2] < 32) {
		pop(availableList, &firstCar);
		firstCar->year = date[0];
		firstCar->month = date[1];
		firstCar->day = date[2];

		insertOrderedByDate(rentedList, &firstCar);
		printf("\nCar with plate: %s was moved to rentedList\n",firstCar->plate);
	} else {
		printf("ERROR: day or month exceeds maximum allowed value\n");
	}
		

}

void choice6(car** availableList, car** rentedList, car** repairList) {
	printf("\nAvailable List:\n");
	printList(availableList);
	printf("\nRented List:\n");
	printList(rentedList);
	printf("\nRepair List:\n");
	printList(repairList);

}





