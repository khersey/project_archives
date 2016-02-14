/*	Name:		newton.h
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		September 15, 2014
 *  
 */

#ifndef NEWTON_H_INCLUDED
#define NEWTON_H_INCLUDED

/*****************************
**	function declarations	**
*****************************/

/*
This function gets input from the user then runs two functions for 
finding the square root of a number, one iterative and one recursive.
It records the time it takes both functions to run and outputs this.
*/
void newton(void);

/*
This function finds uses Newton's method to find the square root of a number recursively.
Newton's Method:
a = x/2
while |a*a-x| <= e
	a = (a+x/a)/2
*/
void recursiveSquareRoot(double x, double e, double a);

/*
This function finds uses Newton's method to find the square root of a number iteratively.
Newton's Method:
a = x/2
while |a*a-x| <= e
	a = (a+x/a)/2
*/
void iterativeSquareRoot(double x, double e, double a);

/*
This function gets valid user input from the user, ensuring they input a positive number.
*/
double getValidDouble(void);

/*
This function returns to absolute value of a value 'input'.
If the double input is negative it is returned as positive.
*/
double absoluteValue(double input);


#endif
