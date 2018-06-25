#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "zero_alloc.h"

int zero_alloc_rec_decr(int x, int i, size_t size1, size_t size2) {
    if(i <= 1) {
        return 0;
    }

    return zero_alloc_rec_multi(x, i-1, size1, size2);
}

int zero_alloc_rec_multi(int x, int i, size_t size1, size_t size2) {
    size_t size;
    int* data;
    int val = -1;

    if(size1 == 0) {
        return 0;
    }

#ifdef CATCH_BAD_PARAM
    if(x > 10 && i < x && size2 == 0) {
        return zero_alloc_rec_multi(x, i-1, size1, size1);
    }
#endif

    if(i < x) {
        size = size2;
    } else {
        size = size1;
    }
    if(i == 10) {
        size2 = size1;
    }

    data = malloc(size);
    if(data) {
        *data = i;
        val = *data * x;
        free(data);
    }

    return zero_alloc_rec_decr(x, i, size1, size2) + val;
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    printf("%i\n", zero_alloc_rec_multi(10, 20, sizeof(int) * 5, 0));
    printf("%i\n", zero_alloc_rec_multi(11, 20, sizeof(int) * 5, sizeof(int) * 6));
#else
    printf("%i\n", zero_alloc_rec_multi(11, 20, sizeof(int) * 5, 0));
#endif

    return 1;
}
#endif
