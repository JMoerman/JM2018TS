#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

void uninit_malloc_if_else_int1(int x, int y) {
    int* data;
    int val;

    if(x <= 10 && x >= y) {
        return;
    }

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

int main() {
    uninit_malloc_if_else_int1(9, 10);
    uninit_malloc_if_else_int1(10, 11);
    uninit_malloc_if_else_int1(11, 10);

    return 1;
}
