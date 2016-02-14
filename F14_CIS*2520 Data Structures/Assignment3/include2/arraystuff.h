/*	Name:		arraystuff.c
 *  Assignment 3: Part 2
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 01, 2014
 *  
 */

#ifndef ARRAYSTUFF_H_INCLUDED
#define ARRAYSTUFF_H_INCLUDED

/*****************************
**	function declarations	**
*****************************/

/*
Control function.  Calls constructHeap to build a heap from the values in arr
the calls downHeap from a loop to sort it.
*/
void sortHeap(int arr[20][10]);

/*
Builds a heap from the values contained in arr.
*/
void constructHeap(int arr[20][10]);

/*
Implements the downheap algorithm.  Moves the object with position root (arr[root][])
downwards through the heap until it is not greater than either of its child leaves.
*/
void downHeap(int arr[20][10], int root, int end);

/*
Prints out the key value of each line (sum of the first 3 values), followed by the items 
contained in each line, for the entire array.
*/
void printArray(int arr[20][10]);

/*
Swaps all 10 values from row item, with all 10 items from row dest.
*/
void swap(int arr[20][10], int item, int dest);

/*
Returns 1 if the object at index item has a lesser value than the object at index dest.
*/
int isLess(int arr[20][10], int item, int dest);


#endif


