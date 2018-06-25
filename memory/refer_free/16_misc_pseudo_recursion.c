#include <stdio.h>
#include <stdlib.h>
#include "refer_free.h"

int refer_free_pseudo_rec1(int x, int y, int i, int** data_ptr) {
    int data_value = **data_ptr;
#ifdef CATCH_BAD_PARAM
    if(x >= y && x <= 10) {
        free(*data_ptr);
        return -1;
    }
#endif

    if(i > 0) {
        free(*data_ptr);
        return 37;
    }

    if(x >= y) {
        free(*data_ptr);
    }

    return data_value + refer_free_pseudo_rec2(x, y, 1, data_ptr);
}

int refer_free_pseudo_rec2(int x, int y, int i, int** data_ptr) {
    int val = 78;
    if(i > 0) {
        if(x <= 10) {
            val += **data_ptr;
        }
        if(x < y) {
            free(*data_ptr);
        }
        return val;
    }

    return 5 + refer_free_pseudo_rec1(x, y, 1, data_ptr);
}

#ifndef NO_MAIN
int main() {
    int* data = malloc(sizeof(int));
    *data = 35;
#ifdef NO_BUG
    printf("%i\n", refer_free_pseudo_rec1(9, 10, 0, &data));
    data = malloc(sizeof(int));
    *data = 35;
    printf("%i\n", refer_free_pseudo_rec1(11, 10, 0, &data));
#else
    printf("%i\n", refer_free_pseudo_rec1(10, 10, 0, &data));
#endif

    return 1;
}
#endif
