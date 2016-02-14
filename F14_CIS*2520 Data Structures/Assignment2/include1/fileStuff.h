/*	Name:		fileStuff.h
 *  Assignment 2: Part 1
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */

#ifndef FILESTUFF_H_INCLUDED
#define FILESTUFF_H_INCLUDED

/*****************************
**	function declarations	**
*****************************/

/*
This function takes a file (fileName) where each line is formatted as %d %d %d %d %s:
mileage year month day plate, and adds them to the list 'top'.  The list will be formatted
depending on the 'mode' where mode == 1 for order by mileage, mode == 2 for order by date 
and mode == 0 for push to front.
*/
void listFromFile(char* fileName, int mode, car** top);

/*
This function writes the linked list 'top' to a file 'fileName'.
*/
void fileFromList(char* fileName, car** top);



#endif


