#include <stdio.h>
#include <stdlib.h>
#include "double_free.h"

int double_free_pseudo_rec1(int x, int y, int i, int** data_ptr) {
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

    return data_value + double_free_pseudo_rec2(x, y, 1, data_ptr);
}

int double_free_pseudo_rec2(int x, int y, int i, int** data_ptr) {
    if(i > 0) {
        if(x <= 10) {
            free(*data_ptr);
        } else if(x > 10 && x < y) {
            free(*data_ptr);
        }
        return -1;
    }

    return 5 + double_free_pseudo_rec1(x, y, 1, data_ptr);
}

#ifndef NO_MAIN
int main() {
    int* data = malloc(sizeof(int));
    if(!data) {
        return -1;
    }
    *data = 35;
#ifdef NO_BUG
    printf("%i\n", double_free_pseudo_rec1(9, 10, 0, &data));
    data = malloc(sizeof(int));
    if(!data) {
        return -1;
    }
    *data = 35;
    printf("%i\n", double_free_pseudo_rec1(11, 10, 0, &data));
#else
    printf("%i\n", double_free_pseudo_rec1(10, 10, 0, &data));
#endif

    return 1;
}
#endif
