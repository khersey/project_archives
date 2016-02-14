/*	Name:		carbon.h
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		September 15, 2014
 *  
 */

#ifndef CARBON_H_INCLUDED
#define CARBON_H_INCLUDED

/*****************************
**	function declarations	**
*****************************/

/* 
This function waits for the user to press enter, and then
runs generateVariant("carbon",0), generating all permutations of 
the word carbon.
*/
void carbon(void);

/*
This function generates all permutations of a string 'inString'
by implementing a recursive backtracking permutation algorithm.
*/
void generateVariant(char* inString, int pos);

/*
This function swaps the value of two characters.
*/
void swapChar(char* first, char* second);


#endif
