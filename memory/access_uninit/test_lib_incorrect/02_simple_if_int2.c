#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

void uninit_malloc_if_else_int2(int x, int y) {
    int* data;
    int val, m, n;

    m = -1;
    n = 5;

    x = x*m+n;


    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    if(x < y) {
        *data = 1;
    }

    if(x > 10) {
        val = 37 * 2;
    } else {
        val = 11 * *data; /* DANGER, if x <= 10 & x >= y */
    }

    printf("x=%i: %i", x, val);

    free(data);
}

