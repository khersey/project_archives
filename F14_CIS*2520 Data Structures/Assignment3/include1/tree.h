/*	Name:		tree.h
 *  Assignment 3: Part 1
 *	Course:		CIS*2520 F14
 *	Author: 	Kyle Hersey
 *	Student #: 	0851973
 *	Date:		October 10, 2014
 *  
 */

#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED


/**************************
**	struct declarations	 **
**************************/

typedef struct leaf leaf;
struct leaf {
	double item;	/* Contains the mathematical value of the leaf (if not an operator) */
	char type;		/* Can be '*', '-', '/', '+', 'x', or ' ' */
	int varCounter; /* If type is 'x' this will contain the number of the variable*/
	leaf * left;
	leaf * right;
};

typedef struct node node;
struct node{
	leaf * value;
	node * next;
};

/*****************************
**	function declarations	**
*****************************/

/*
Parses the input function, creating leafs from each element, and storing them in a stack.  
Whenever a ')' is found in the input string, elements are removed from the first stack
and moved to the second in such a way that this second stack contains the equation in 
postfix notation, but in reverse.  The equations is then popped and pushed between stacks
to order the equation forwards.
*/
void processInput(char * inStr, node ** opStack, node ** doneStack);

/*
Creates binary tree from a stack containing the equation in postfix notation.
*/
void buildTree(node ** postfixStack, node ** opStack, leaf ** root);

/*
Recursively prints out the binary tree from the top down.
*/
void preOrderTraversal(leaf * root);

/*
Recursively prints out the binary tree from the left to the right.
*/
void inOrderTraversal(leaf * root);

/*
Recursively prints out the binary tree from the bottom up. 
*/
void postOrderTraversal(leaf * root);

/*
Calls getVarFromUser(), to get user input, and then passes this to doSearch()
*/
void updateVar(leaf ** root);

/*
Function gets a variable and value from the user and constructs a leaf with this data.
*/
leaf * getVarFromUser(void);

/*
Recursively search the tree looking for a node with a varCounter matching searchTerm.
If the node is found, it's item value will be replaced by the valkue of searchTerm's
item, and the function returns 1.
*/
int doSearch(leaf * root, leaf * searchTerm);

/*
Sets up and calls doCalculation()
*/
void runCalculation(leaf ** root);

/*
Recursively calculates the value of the binary tree.
*/
double calculation(leaf * root);

/*
Applies operation op to varaibles left and right, and returns the result.  format is (left) (op) (right).
examples: left = 4, op = -, right = 7
4-7 = -3
*/
double eval(double left, char op, double right);

/*
Allocates memory for newleaf and populates its variables with the varaibles being passed in.
*/
void fillLeaf(leaf** newLeaf, double item, char type, int varCounter);

/*
prints out the value of an individual leaf.
*/
void printLeaf(leaf * printMe);

/*
Draws out the binary tree recursively.

This code is based off of code found at http://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console
written by an annonymous user, but has been customized to fit my needs.
(originally _print_t)
*/
int drawTree(leaf *tree, int is_left, int offset, int depth, char s[20][255]);

/*
Function to populate a string array and pass it to drawTree().

This code is based off of code found at http://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console
written by an annonymous user, but has been customized to fit my needs.
(originally print_t)
*/
void startDrawTree(leaf *tree);

/*
This function recursively goes through the code from top down and prints out all variables and their values.
*/
void printVarValues(leaf * root);

/*
Creates a node object containing a leaf struct and pushes it to the top of a stack.
*/
void push(node** top, leaf ** value);

/*
Removes the top element from a stack and returns its contained leaf struct.
*/
leaf * pop(node** top);

/*
prints out every item in a stack. Purely for debugging.
*/
void printStack(node ** top);



#endif
