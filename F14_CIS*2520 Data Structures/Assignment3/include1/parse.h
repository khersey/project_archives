/*	Name:		parse.h
 *  Assignment 3: Part 1
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */

#ifndef POSTFIXER_H_INCLUDED
#define POSTFIXER_H_INCLUDED

/*****************************
**	function declarations	**
*****************************/

/*
Searches through the string inStr starting a index pos, and returns the position
of the first character that is not a digit or a '.'
*/
int getNextPos(int pos, char * inStr);

/*
Creates a substring of inStr between start and end indexes.  This substring WILL
ALWAYS contain either an integer or a floating point value.  This value is parsed out
and returned as a double.
*/
double getNumber(int start, int end, char * inStr);

#endif
