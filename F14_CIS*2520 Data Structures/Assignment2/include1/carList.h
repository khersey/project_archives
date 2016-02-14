/*	Name:		carList.h
 *  Assignment 2: Part 1
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */

#ifndef CARLIST_H_INCLUDED
#define CARLIST_H_INCLUDED

/**************************
**	struct declarations	 **
**************************/

typedef struct car car;
struct car {
	int mileage;
	char* plate;
	int year;
	int month;
	int day;
	car * next;
};


/*****************************
**	function declarations	**
*****************************/

/*
This function creates a newCar 'car' struct pointed to by the pointer newCar, using
the other parameter values.
*/
void constructCar(car** newCar, int mileage, char* plate, int year, int month, int day);

/*
This function compares two car structs and returns 0 
if they are equal and 1 if they are not.
*/
int equals(car** first, car** second);

/*
This function compares the date values of two car structs.  If the first is larger
than the second it will return 1.  If the first is smaller than the second it will 
return -1.  If the dates are equal it will return 0;
*/
int dateCompare(car** first, car** second);

/*
This function systematically frees every element in a linked list pointed to by 'top'.
*/
void destroyList(car** top);

/*
This function frees a car struct as well as its plate string.
*/
void destroyCar(car** someCar);

/*
This function inserts a car pointed to by 'newCar' into an ordered position in a linked
list determined by 'newCar's mileage, where the car with the lowest mileage is at the
front of the list.
*/
void insertOrderedByMileage(car** top, car** newCar);

/*
This function inserts a car pointed to by 'newCar' into the first position of a linked 
list pointed to by 'top'.
*/
void insertToFront(car** top, car** newCar);

/*
This function inserts a car pointed to by 'newCar' into an ordered position in a linked
list determined by 'newCar's date, where the car with the lowest date is at the
front of the list.
*/
void insertOrderedByDate(car** top, car** newCar);

/*
This fucntion removes the first node from a link list pointed to by 'top' and pointing 'current' to
this node.
*/
void pop(car** top, car** current);

/*
This function systematically prints out every element in a linked list.
*/
void printList(car** top);

/*
This fucntion prints out the values in a car struct 'element'.
*/
void printCar(car** element);

/*
This function finds and removes a car element where 'carPtr->plate' matches 'plate', from linked list
'top'.  If this list DOES NOT contain an element with a matching plate it will return NULL;
*/
void extractFromList(car** top, char* plate, car** carPtr);






#endif


