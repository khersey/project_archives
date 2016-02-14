/*	Name:		menu.h
 *  Assignment 2: Part 1
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/*****************************
**	function declarations	**
*****************************/

/*
This function dispays the menu and ensures the user displays a valid integer between 1-7.
*/
int menu(void);

/*
This function calls the appropriate choice function and passes the appropriate list pointers
to it.  The double returned is the cost of the transaction, by default 0.
*/
double executeChoice(int choice, car** availableList, car** rentedList, car** repairList);

/*
This function creates a new car struct and adds it to the availableList linked list.
*/
void choice1(car** availableList);

/*
This function moves a car from the rentedList to the availableList, return the transaction cost.
*/
double choice2(car** rentedList, car** availableList);

/*
This function moves a car from the rentedList to the repairList return the transaction cost.
*/
double choice3(car** rentedList, car** repairList);

/*
This function moves a car from the repairList to the availableList.
*/
void choice4(car** repairList, car** availableList);

/*
This function moves the first car in the available list to the rentedList.
*/
void choice5(car** availableList, car** rentedList);

/*
This function prints out all three linked lists.
*/
void choice6(car** availableList, car** rentedList, car** repairList);




#endif


