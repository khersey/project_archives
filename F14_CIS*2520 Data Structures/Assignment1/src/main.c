/*	Name:		ackermann.c
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		September 15, 2014
 *  
 */


#include <stdio.h>
#include "ackermann.h"
#include "carbon.h"
#include "newton.h"

int main(void) {
	
	printf("ackermann() starting\n");
	ackermann();
	printf("ackermann() done\n");
	

	printf("carbon() starting\n");
	carbon();
	printf("carbon() done\n");
	

	printf("newton() starting\n");
	newton();
	printf("newton() done\n");
	
	return 0;
	
}

