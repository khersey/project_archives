/* filename:   iterative_ackermann.c
 * author:     Michael Wirth
 *             (From Courselink)
 * course:     CIS*3190
 * assignment: 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define STACKSIZE 1000000

/* Iterative Ackermann from Courselink */

struct dataT {
    int m;
};

struct stack {
    int top;
    struct dataT items[STACKSIZE];
} st;

void createstack() {
    st.top = -1;
}

int isFULL() {
    if (st.top >= STACKSIZE-1) {
        return 1;
    } else {
        return 0;
    }
}

int isEMPTY() {
    if (st.top == -1) {
        return 1;
    } else {
        return 0;
    }
}

int stack_size() {
    return st.top;
}

int top() {
    return st.items[st.top].m;
}

void push(int m) {
    if (isFULL()) {
        fputs("Error: stack overflow\n", stderr);
        abort();
    } else {
        st.top ++;
        st.items[st.top].m = m;
    }
}

void pop(int *m) {
    if(isEMPTY()) {
        fputs("Error: stack underflow\n", stderr);
        abort();
    } else {
        *m = st.items[st.top].m;
        st.top --;
    }
}

int ackermann(int m, int n) {
    push(m);
    while(!isEMPTY()) {
        pop(&m);
        if(m == 0) {
            n ++;
        } else if(n == 0) {
            n = 1;
            push(m-1);
        } else {
            n --;
            push(m-1);
            push(m);
        }
    }
    return n;
}

int main() {
    int r, m, n;
    struct timeval t1, t2, tv;

    createstack();
    printf("Enter m and n: ");
    scanf("%d%d", &m, &n);

    gettimeofday(&t1,NULL);

    r = ackermann(m,n);

    gettimeofday(&t2,NULL);

    printf("Result = %d\n", r);
    timersub(&t2, &t1, &tv);
    printf("%ld milliseconds\n", (1000000*tv.tv_sec + tv.tv_usec)/1000);

    return 0;
}
