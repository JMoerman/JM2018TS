#include <stdio.h>
#include <stdlib.h>
#include "zero_alloc.h"

int zero_alloc_pseudo_rec1(int x, int y, int i, size_t size1, size_t size2) {
#ifdef CATCH_BAD_PARAM
    if(x >= y && x <= 10) {
        return -1;
    }
#endif

    if(i > 0) {
        return 37;
    }

    if(x < y) {
        size2 += sizeof(int);
    } else {
        size1 += sizeof(int);
    }

    return zero_alloc_pseudo_rec2(x, y, 1, size1, size2);
}

int zero_alloc_pseudo_rec2(int x, int y, int i, size_t size1, size_t size2) {
    size_t size;
    int* data;
    int val = -1;

    if(i <= 0) {
        return 5 + zero_alloc_pseudo_rec1(x, y, 1, size1, size2);
    }

    if(x > 10) {
        size = size1 + sizeof(int);
    } else {
        size = size2;
    }

    data = malloc(size);
    if(data) {
        *data = x;
        val = *data * y;
        free(data);
    }
    return val;
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    printf("%i\n", zero_alloc_pseudo_rec1(9, 10, 0, sizeof(int), 0));
    printf("%i\n", zero_alloc_pseudo_rec1(10, 10, 0, 0, sizeof(int)));
    printf("%i\n", zero_alloc_pseudo_rec1(11, 10, 0, sizeof(int), 0));
#else
    printf("%i\n", zero_alloc_pseudo_rec1(10, 10, 0, sizeof(int), 0));
#endif

    return 1;
}
#endif
