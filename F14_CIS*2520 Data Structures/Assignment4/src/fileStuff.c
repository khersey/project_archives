/*  Name:       fileStuff.c
 *  Assignment 4
 *  Course:     CIS*2520 F14
 *  Author:     Kyle Hersey
 *  Student #:  0851973
 *  Date:       November 20, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileStuff.h"
#include "utility.h"

void readFromFile(stack **root) {
    int lineLength, i, keyPos;
    char *key = NULL;
    char *fileName = NULL;
    char buffer[2048];
    char c;
    FILE *file;

    printf("filename: ");
    fileName = getString();

    file = fopen(fileName,"r");

    while (fgets(buffer, sizeof(buffer), file)) {
        lineLength = strlen(buffer);
        key = malloc(10);
        keyPos = 0;
        for(i = 0; i < lineLength; i++) {
            c = buffer[i];
            if( c != '\n' && c != ' ' && c != '\t') {
                if(keyPos > strlen(key)-1) {
                    key = realloc(key, sizeof(key) + 10);
                }
                key[keyPos] = c;
                keyPos ++;
            } else if(keyPos > 0) {
                push(root,key);
                keyPos = 0;
                key = malloc(10);
            }

        }

        if(strlen(key) > 0) {
            printf("ERROR: half a key is missing: %s\n",key);
            free(key);
        }

    }

    fclose(file);
}

void push (stack **root, char *key) {
    stack *newNode = malloc(sizeof(stack));
    if (!newNode) death(-1,"new Stack Node");
    newNode->key = key;
    newNode->next = *root;
    *root = newNode;
}

char * pop(stack **root) {
    stack *temp;
    char *key;
    if (!(*root)) death(-2,"cannot pop from NULL stack");
    temp = *root;
    *root = temp->next;
    key = temp->key;
    free(temp);
    return key;
}





