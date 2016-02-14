/*	Name:		utility.h
 *  Assignment 3: Part 1
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
Displays a menu, and returns the user's selection.
*/
int menu(void);

/*
Clears the input buffer.
*/
void clearBuffer(void);

/*
Returns 1 if c is one of { - + / * }.
*/
int isOp(char c);

/*
Function to kill program if something goes horribly wrong.
Will print a different error message depending on the code received
before exiting.
*/
void death(int code);

#endif
