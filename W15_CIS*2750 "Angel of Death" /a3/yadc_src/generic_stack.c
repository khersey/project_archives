/* filename:   generic_stack.c
 * author:     Kyle Hersey
 * student#:   0851973
 * course:     this code was designed to be used in any course.
 *
 * This file contains functions for implementing a generic stack.
 */

#include "generic_stack.h"

stack stack_init(void) {
    stack st = malloc(sizeof(generic_stack));
    st->head = NULL;
    return st;
}

void stack_push(stack st, void * data) {
    sNode * node;
    node = malloc(sizeof(sNode));
    node->data = data;

    node->next = st->head;
    st->head = node;
}

void * stack_pop(stack st) {
    void * out;
    sNode * temp;
    if(st->head == NULL) return NULL;

    out = st->head->data;

    temp = st->head;

    st->head = st->head->next;

    free(temp);

    return out;

}

void * stack_top(stack st) {
    if(st->head == NULL) return NULL;
    return st->head->data;
}

