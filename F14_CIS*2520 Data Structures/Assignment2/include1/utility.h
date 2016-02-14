/*	Name:		utility.h
 *  Assignment 2: Part 1
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

/*****************************
**	function declarations	**
*****************************/


/*
This function cleans this input buffer of STDIN.
*/
void clearBuffer(void);

/*
This function gets a string from the user and returns it as a character pointer.
*/
char * getPlate(void);

/* 
This functions expects an integer array to be passed in, that has been initialized
as follows: int date[3] = {0,0,0};  It asks for user input and if input is input appropriatly 
will return a year, month, and date value where date[0] = year, date[1] = month and date[2] = 
day.
*/
void getDate(int * date);

/*
This function asks the user to enter an integer larger than 'baseline' and returns it.  This
ensures the new mileage is positive and larger than the old one. 
*/
int getMileage(int baseLine);

/*
This function calculates the transaction cost of a returned rental. The cost is calculated as 
such: $40 + $0.15 for every km over the first 100.
*/
float calculateTransaction(int startMileage, int endMileage);



#endif

