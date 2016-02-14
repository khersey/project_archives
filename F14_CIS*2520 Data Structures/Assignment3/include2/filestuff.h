/*	Name:		filestuff.c
 *  Assignment 3: Part 2
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 01, 2014
 *  
 */

#ifndef FILESTUFF_H_INCLUDED
#define FILESTUFF_H_INCLUDED

/*****************************
**	function declarations	**
*****************************/

/*
Loads items from the file f.dat into an array.
*/
void loadArray(int arr[20][10]);

/*
returns the next integer after index in inStr.
*/
int getNextInt(int index, char inStr[128]);



#endif

