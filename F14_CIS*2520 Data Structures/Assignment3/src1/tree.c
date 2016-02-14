/*	Name:		tree.c
 *  Assignment 3: Part 1
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "utility.h"
#include "parse.h"

void processInput(char * inStr, node ** opStack, node ** doneStack) {
	int pos = 0;
	int end = 0;
	char c = ' ';
	leaf * tempLeaf = NULL;
	double num = 0.0;
	int varNum = 0;
	int length = strlen(inStr);

	for(pos = 0; pos < length; pos ++) {
		c = inStr[pos];
		printStack(opStack);   /* DEBUG */
		printStack(doneStack); /* DEBUG */
		if(isOp(c)) {
			fillLeaf(&tempLeaf, 0.0, c, 0);
			push(opStack,&tempLeaf);
		} else if(c == ')') {
			do {
				tempLeaf = pop(opStack);
				if(tempLeaf->type != '(') {
					push(doneStack,&tempLeaf);
				} else {
					break;
				}
			} while(*opStack);

		} else if(c == 'x') {
			pos++;
			end = getNextPos(pos,inStr);
			varNum = (int)getNumber(pos,end,inStr);
			pos = end;
			pos--;
			fillLeaf(&tempLeaf,0.0,'x',varNum);
			push(doneStack,&tempLeaf);
		} else if(c == '\n' || c == ' ') {
			/* do nothing */
		} else if(isdigit(c)) {
			end = getNextPos(pos,inStr);
			num = getNumber(pos,end,inStr);
			pos = end;
			pos --;
			fillLeaf(&tempLeaf,num, ' ', 0);
			push(doneStack,&tempLeaf);
		} else {
			printf("ERROR: unexpected character %c\n",c);
			death(1);
		}
	}

	while(*opStack) {
		tempLeaf = pop(opStack);
		if(tempLeaf->type != '(') {
			push(doneStack,&tempLeaf);
		}
	}

	while(*doneStack) { 
		tempLeaf = pop(doneStack);
		push(opStack,&tempLeaf);
	}
}

void buildTree(node ** postfixStack, node ** opStack, leaf ** root) {
	leaf *tempLeaf, *tempRight, *tempLeft;
	tempLeaf = NULL;
	tempLeft = NULL;
	tempRight = NULL;

	while(*postfixStack) {
		tempLeaf = pop(postfixStack);
		if(isOp(tempLeaf->type)) {
			tempRight = pop(opStack);
			tempLeft = pop(opStack);
			tempLeaf->right = tempRight;
			tempLeaf->left = tempLeft;
			push(opStack,&tempLeaf);
		} else {
			push(opStack,&tempLeaf);
		}
	}

	*root = pop(opStack);
	if(*opStack) {
		printf("ERROR: opStack still contains one or more ");
		printStack(opStack);
		death(2);
	}
}

void preOrderTraversal(leaf * root) {
	if(root) {
		printLeaf(root);
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}
}

void inOrderTraversal(leaf * root) {
	if(root) {
		inOrderTraversal(root->left);
		printLeaf(root);
		inOrderTraversal(root->right);
	}
}

void postOrderTraversal(leaf * root) {
	if(root) {
		postOrderTraversal(root->left);
		postOrderTraversal(root->right);
		printLeaf(root);
	}
}

void updateVar(leaf ** root) {
	leaf * searchTerm;
	int success = 0;

	searchTerm = getVarFromUser();

	printf("\n\nSearching.");
	success = doSearch(*root, searchTerm);
	printf("\n");

	if(success == 0) {
		printf("Sorry we could not find a variable called x%d\n",searchTerm->varCounter);
	} else {
		printf("Variable successfully updated!\n");
	}

}

leaf * getVarFromUser(void) {
	leaf * output;
	int varNum;
	double item;
	int done;

	int pos, end, length;
	char c;
	char * inStr;
	inStr = malloc(256);
	done = 0;

	do {
		clearBuffer();

		printf("Input format: variable_name, variable_data\n>");
		fgets(inStr, sizeof(inStr), stdin);

		length = strlen(inStr);

		for(pos = 0; pos < length; pos++) {
			c = inStr[pos];

			if(c == 'x') {
				pos++;
				end = getNextPos(pos,inStr);
				varNum = (int)getNumber(pos,end,inStr);
				pos = end;
				pos--;
				done ++;
			} else if(isdigit(c) && done <2) {
				end = getNextPos(pos,inStr);
				item = getNumber(pos,end,inStr);
				pos = end;
				pos --;
				done ++;
			}
		}

	} while(done < 2);

	fillLeaf(&output, item, 'x', varNum);

	free(inStr);
	return output;
}

int doSearch(leaf * root, leaf * searchTerm) {
	printf(".");
	if(!root) {
		return 0;
	}

	if(root->type == searchTerm->type && root->varCounter == searchTerm->varCounter) {
		root->item = searchTerm->item;
		return 1;
	} else if(doSearch(root->left,searchTerm) == 1 || doSearch(root->right,searchTerm) == 1){
		return 1;
	} else {
		return 0;
	}
}

void runCalculation(leaf ** root) {
	double result;

	printf("running calculations");

	result = calculation(*root);

	printf("\nResult: %f\n",result);
}

double calculation(leaf * root) {
	double left;
	double right;
	printf(".");

	if(isOp(root->type)) {
		left = calculation(root->left);
		right = calculation(root->right);

		return eval(left,root->type,right);

	} else {
		return root->item;
	}
}

double eval(double left, char op, double right) {
	if(op == '-') {
		return left - right;
	} else if(op == '+') {
		return left + right;
	} else if(op == '*') {
		return left * right;
	} else {
		if(right != 0.0) {
			return left / right;
		} else {
			death(0);
			return 0; /* unecesary, but removes a warning */
		}
	}
}

void fillLeaf(leaf** newLeaf, double item, char type, int varCounter) {
	*newLeaf = malloc(sizeof(leaf));
	if(!(*newLeaf)) death(-1);
	(*newLeaf)->item = item;
	(*newLeaf)->type = type;
	(*newLeaf)->varCounter = varCounter;
	(*newLeaf)->left = NULL;
	(*newLeaf)->right = NULL;
	printLeaf(*newLeaf);
}

void printLeaf(leaf * printMe) {
	if (printMe) {
		if(isOp(printMe->type) || printMe->type == '(') {
			printf("LEAF: %c\n",printMe->type);
		} else if (printMe->type == 'x') {
			printf("LEAF: x%d=%0.2f\n",printMe->varCounter, printMe->item);
		} else {
			printf("LEAF: %0.2f\n",printMe->item);
		}
	}
	
}

int drawTree(leaf *tree, int is_left, int offset, int depth, char s[20][255]) {
    char b[20];
    int width = 5;
    int i, left, right;

    if (!tree) return 0;

    if(isOp(tree->type)) {
    	sprintf(b, "  %c  ", tree->type);
    } else if(tree->type == 'x') {
    	sprintf(b, " x%02d ", tree->varCounter);
    } else {
    	sprintf(b, "%05.2f", tree->item);
    }

    left  = drawTree(tree->left,  1, offset,                depth + 1, s);
    right = drawTree(tree->right, 0, offset + left + width, depth + 1, s);

    for (i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }

    return left + width + right;
}

void startDrawTree(leaf *tree) {
    char s[20][255];
    int i;

    for (i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    drawTree(tree, 0, 0, 0, s);

    for (i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

void printVarValues(leaf * root) {
	if(root) {
		if(root->type == 'x') {
			printf("x%d = %f\n",root->varCounter, root->item);
		}
		printVarValues(root->left);
		printVarValues(root->right);
	}
}

/*

	STACK STUFF

 */

void push (node** top, leaf ** value) {
	node * newNode = malloc(sizeof(node));
	if (!newNode) death(-1);
	printf("push()\n");
	newNode->value = *value;
	newNode->next = *top;
	*top = newNode;
}

leaf * pop(node** top) {
	leaf * value;
	node* temp;
	printf("pop()\n");
	if (!(*top)) death(3);
	temp = *top;
	*top = temp->next;
	value = temp->value;
	return value;
}

void printStack(node ** top) {
	node * current;
	current = *top;

	printf("Stack Items:\n");
	if( current != NULL ) {
		while( current ) {
			printf("in while loop\n");
			printLeaf(current->value);
			current = current->next;
		}
	}

	
}



