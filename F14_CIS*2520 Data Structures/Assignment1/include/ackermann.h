/*	Name:		ackermann.h
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		September 15, 2014
 *  
 */
 
#ifndef ACKERMANN_H_INCLUDED
#define ACKERMANN_H_INCLUDED

/*****************************
**	function declarations	**
*****************************/

/*
This function gets input and then passes it to/ runs the runAckermann() function
*/
void ackermann(void);

/* 
This function ensures the user enters a valid integer in the provided range
from 0 to maxSize.
*/
int getIntInput(int maxSize);

/*
This function recursively find the results of the ackermann function:
A(0,n) = n + 1
A(m,0) = A(m-1,1)
A(m,n) = A(m-1,A(m,n-1))
*/
int runAckermann(int m, int n);

/*
This function clears the input buffer
*/
void clearBuffer(void);


#endif
