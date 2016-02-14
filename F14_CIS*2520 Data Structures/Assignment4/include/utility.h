/*  Name:       utility.h
 *  Assignment 4
 *  Course:     CIS*2520 F14
 *  Author:     Kyle Hersey
 *  Student #:  0851973
 *  Date:       November 20, 2014
 *  
 */

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED


void death(int errorCode, const char *errorMessage);

char * getString(void);

int getInt(void);

int menu(void);

void clearBuffer(void);

int max(int x, int y);


#endif
