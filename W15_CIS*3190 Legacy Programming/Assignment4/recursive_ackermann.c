/*
* filename:   recursive_ackermann.c
* student:    Kyle Hersey
* student#:   0851973
* course:     CIS*3190
* assignment: 4

* Time to run: 0m48.556s
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int ackermann(int m, int n);


int main() {
    int m, n, r;
    struct timeval t1, t2, tv;

    printf("Please enter m and n: ");
    scanf("%d%d", &m, &n);

    gettimeofday(&t1, NULL);
    r = ackermann(m, n);
    gettimeofday(&t2, NULL);

    printf("Resylt = %d\n", r);
    timersub(&t2, &t1, &tv);
    printf("%ld milliseconds\n", (10000000*tv.tv_sec + tv.tv_usec)/1000);

    return 0;
}

int ackermann(int m, int n) {
    if(m == 0) {
        return n+1;
    } else if(n == 0) {
        return ackermann(m-1, 1);
    } else {
        return ackermann(m-1, ackermann(m, n-1));
    }
}
