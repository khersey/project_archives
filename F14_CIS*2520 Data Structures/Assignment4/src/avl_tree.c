/*	Name:		avl_tree.c
 *  Assignment 4
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		November 20, 2014
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl_tree.h"
#include "utility.h"

void createNode(node **newNode, char *key) {
	*newNode = malloc(sizeof(node));
	if(!(*newNode)) death(-1,"new Node struct");
	(*newNode)->key = key;
	(*newNode)->count = 1;
	(*newNode)->height = 0;
	(*newNode)->right = NULL;
	(*newNode)->left = NULL;
}

void destroyTree(node *root) {
	if (root != NULL) {
		destroyTree(root->left);
		destroyTree(root->right);
		free(root->key);
		free(root);
	}
}

node * leftRotate(node *root) {
	node *temp = NULL;

	temp = root->left;
	root->left = temp->right;
	temp->right = root;

	root->height = max(height(root->left), height(root->right)) + 1;
	temp->height = max(height(temp->left), root->height) + 1;

	return temp;
}

node * rightRotate(node *root) {
	node *temp = NULL;

	temp = root->right;
	root->right = temp->left;
	temp->left = root;

	root->height = max(height(root->left), height(root->right)) + 1;
	temp->height = max(height(temp->right), root->height) + 1;

	return temp;
}

node * doubleLeftRotate(node *root) {
	root->left = rightRotate(root->left);
	root = leftRotate(root);
    return root;
}

node * doubleRightRotate(node *root) {
	root->right = leftRotate(root->right);
	root = rightRotate(root);
    return root;
}

node * insert(node *root, char *key) {

	if (root == NULL) {
		root = malloc(sizeof(node));
        root->key = key;
        root->count = 1;
        root->height = 0;
        root->right = NULL;
        root->left = NULL;

	} else if (strcmp(key, root->key) < 0) {
		root->left = insert(root->left, key);
		if (height(root->left) - height(root->right) == 2) {
			if (strcmp(key, root->left->key) < 0) {
				root = leftRotate(root);
			} else {
				root = doubleLeftRotate(root);
			}
		}

	} else if (strcmp(key, root->key) > 0) {
		root->right = insert(root->right, key);
		if(height(root->right) - height(root->left) == 2) {
			if (strcmp(key, root->right->key) > 0) {
				root = rightRotate(root);
			} else {
				root = doubleRightRotate(root);
			}
		}

	} else {
        root->count += 1;
    }

	root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}


node * deletion(node *root, char *key) {
    int balance;
    node *temp;

    if (!root) {
        return NULL;
    }

    if (strcmp(key, root->key) < 0) {
        root->left = deletion(root->left, key);
    } else if (strcmp(key, root->key) > 0) {
        root->right = deletion(root->right, key);
    } else {
        if (root->count == 1) {
            if (root->left == NULL) {
                temp = root;
                root = root->right;
                free(temp);
            } else if (root->right == NULL) {
                temp = root;
                root = root->left;
                free(temp);
            } else {
                temp = root->right;
                while (temp->left != NULL) {
                    temp = temp->left;
                }
                free(root->key);
                root->key = temp->key;
                root->right = deletion(root->right, temp->key);
            }
        } else {
            root->count -= 1;
            return root;
        }

    }

    if (!root) {
        return NULL;
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        return doubleLeftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        return doubleRightRotate(root);
    }

    return root;

}


void findHandler(node *root, char *key) {
    node *output = NULL;

    output = find(root, key);

    if(output == NULL) {
        noSuchKey();
    } else {
        printNode(output);
    }
}

node * find(node *root, char *key) {
    if (root) {
        if (strcmp(key, root->key) == 0) {
            return root;
        } else if (strcmp(key, root->key) < 0) {
            return find(root->left, key);
        } else if (strcmp(key, root->key) > 0) {
            return find(root->right, key);
        }
    }
    return NULL;
}

void findAll(node *root, int count) {
    if (root) {
        findAll(root->left, count);
        if (root->count >= count) {
            printNode(root);
        }
        findAll(root->right, count);
    }
}

void testTree(node *root) {
    if (root) {
        testTree(root->left);
        printf("\n");
        testTree(root->right);
    }
}

void printNode(node *root) {
    printf("key: %s, frequency: %d\n", root->key, root->count);
}

void noSuchKey(void) {
    printf("no_such_key\n");
}

int getBalance(node *root) {
    if(root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

int height(node *item) {
	if (item == NULL) {
		return -1;
	} else {
		return item->height;
	}
}

int count(node *root) {
    int c = 0;

    if (root != NULL) {
        c = 1;
        c += count(root->right);
        c += count(root->left);
    }

    return c;
}

void getHeightSize(node *root) {
    int h = 0;
    int c = 0;

    h = height(root);
    c = count(root);

    printf("height: %d, size: %d\n",h,c);
}


