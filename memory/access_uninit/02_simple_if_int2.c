#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

void uninit_malloc_if_else_int2(int x, int y) {
    int* data;
    int val, m, n;

    m = -1;
    n = 5;

    x = x*m+n;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif

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

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_malloc_if_else_int2(-4, 11);
    uninit_malloc_if_else_int2(-5, 11);
    uninit_malloc_if_else_int2(-6, 11);
#else
    uninit_malloc_if_else_int2(-4, 10); /* OK */
    uninit_malloc_if_else_int2(-5, 10); /* DANGER */
    uninit_malloc_if_else_int2(-6, 10); /* OK */
#endif

    return 1;
}
#endif
