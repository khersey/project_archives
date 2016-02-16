/* filename:   generic_stack.h
 * author:     Kyle Hersey
 * student#:   0851973
 * course:     this code was designed to be used in any course.
 *
 * This file contains function and type declarations for implementing a generic stack.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct sNode sNode;
struct sNode {
    void * data;
    sNode * next;
};

typedef struct generic_stack generic_stack;
struct generic_stack
{
    sNode * head;
};

typedef generic_stack* stack;


stack stack_init(void); 

void stack_push(stack st, void * data);

void * stack_pop(stack st);

void * stack_top(stack st);
