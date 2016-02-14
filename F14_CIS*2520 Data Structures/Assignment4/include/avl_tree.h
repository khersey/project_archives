/*	Name:		avl_tree.h
 *  Assignment 4
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 20, 2014
 *  
 */

#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED


typedef struct node node;
struct node {
	char *key;
	int count;
	int height;
	node *right;
	node *left;
};


void createNode(node **newNode, char *key);

void destroyTree(node *head);

node * leftRotate(node *root);

node * rightRotate(node *root);

node * doubleLeftRotate(node *root);

node * doubleRightRotate(node *root);

node * insert(node *root, char *key);

node * deletion(node *root, char *key);

void findHandler(node *root, char *key);

node * find(node *root, char *key);

void findAll(node *root, int count);

void printNode(node *root);

void noSuchKey(void);

int getBalance(node *root);

int height(node *item);

int count(node *root);

void getHeightSize(node *root);


#endif


