/*	Name:		arraystuff.c
 *  Assignment 3: Part 2
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 01, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arraystuff.h"

void sortHeap(int arr[20][10]) {
	int end;
	end = 19;

	constructHeap(arr);

	while(end > 0) {
		swap(arr, 0, end);
		end --;
		downHeap(arr, 0, end);
	}
}

void constructHeap(int arr[20][10]) {
	int start = 9;
	while(start >= 0) {
		downHeap(arr, start, 19);
		start --;
	}
}

void downHeap(int arr[20][10], int root, int end) {
	int child;
	int item = root;

	while((item * 2 + 1) < end) {
		child = item * 2 + 1;
		item = root;
		if(isLess(arr, item, child)) {
			item = child;
		}
		if(child+1 < end && isLess(arr, item, child+1)) {
			item = child+1;
		}
		if(item != root) {
			swap(arr, item, root);
			root = item;
		} else {
			break;
		}
	}
}

void printArray(int arr[20][10]) {
	int i, j;

	for(i = 0; i < 20; i++) {
		printf("KEY: %03d   Object: ", arr[i][0] + arr[i][1] + arr[i][2]);
		for(j = 0; j < 10; j++) {
			if(arr[i][j] != 0){
				printf("%02d ",arr[i][j]);
			} else {
				printf("00 ");
			}
			
		}
		printf("\n");
	}
}

void swap(int arr[20][10], int item, int dest) {
	int temp[10];
	int j;

	for(j = 0; j < 10; j++) {
		temp[j] = arr[dest][j];
	}
	for(j = 0; j < 10; j++) {
		arr[dest][j] = arr[item][j];
	}
	for(j = 0; j < 10; j++) {
		arr[item][j] = temp[j];
	}
}

int isLess(int arr[20][10], int item, int dest) {
	int itemSum;
	int destSum;

	itemSum = arr[item][0] + arr[item][1] + arr[item][2];
	destSum = arr[dest][0] + arr[dest][1] + arr[dest][2];

	if(itemSum < destSum) {
		return 1;
	} else {
		return 0;
	}

}

