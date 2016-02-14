/*	Name:		main.c
 *  Assignment 4
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 20, 2014
 *  
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "avl_tree.h"
#include "fileStuff.h"
#include "utility.h"


int main(void) {
    int choice = 0;
    node *root = NULL;
    stack *keyStack = NULL;
    char *key = NULL;
    int frequency = 0;

    printf("CIS*2520 - Assignment 4: AVL TREES\n");
    printf("Author:    Kyle Hersey\n");
    printf("Student #: 0851973\n\n");

    do {

        choice = menu();

        if (choice == 1) {
            readFromFile(&keyStack);
            while(keyStack != NULL) {
                root = insert(root, pop(&keyStack));
            }
        } else if (choice == 2) {
            printf("find key: ");
            key = getString();
            findHandler(root,key);
            free(key);
        } else if (choice == 3) {
            printf("insert key: ");
            key = getString();
            root = insert(root, key);
            findHandler(root,key);
            free(key);
        } else if (choice == 4) {
            printf("remove key: ");
            key = getString();
            root = deletion(root, key);
            findHandler(root,key);
            free(key);
        } else if (choice == 5) {
            getHeightSize(root);
        } else if (choice == 6) {
            printf("frequency: ");
            frequency = getInt();
            findAll(root, frequency);
        }


    } while(choice != 7);

    destroyTree(root);
	return 0;
}

