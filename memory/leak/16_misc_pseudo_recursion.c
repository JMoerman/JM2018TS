#include <stdio.h>
#include <stdlib.h>
#include "memory_leak.h"

int mem_leak_pseudo_rec1(int x, int y, int i, int** data_ptr) {
    int data_value;

    if(!*data_ptr) {
        *data_ptr = malloc(sizeof(int));
        if(!*data_ptr) {
            return -1;
        }
        **data_ptr = -37;
    }

    data_value = **data_ptr;
#ifdef CATCH_BAD_PARAM
    if(x >= y && x < 10) {
        free(*data_ptr);
        return -1;
    }
#endif

    if(i > 0) {
        free(*data_ptr);
        return 37;
    }

    if(x < y) {
        free(*data_ptr);
        *data_ptr = 0;
    } else {
        (**data_ptr)++;
    }

    return data_value + mem_leak_pseudo_rec2(x, y, 1, data_ptr);
}

int mem_leak_pseudo_rec2(int x, int y, int i, int** data_ptr) {
    int val = 78;
    if(i <= 0) {
        return 5 + mem_leak_pseudo_rec1(x, y, 1, data_ptr);
    }

    if(x < 10) {
        val += 2;
    } else {
        if(*data_ptr) {
            val -= **data_ptr;
            free(*data_ptr);
            *data_ptr = 0;
        }
    }
    return val;
}

#ifndef NO_MAIN
int main() {
    int* data = malloc(sizeof(int));
    if(!data) {
        return -1;
    }
    *data = 35;
#ifdef NO_BUG
    printf("%i\n", mem_leak_pseudo_rec1(9, 10, 0, &data));
    data = malloc(sizeof(int));
    if(!data) {
        return -1;
    }
    *data = 35;
    printf("%i\n", mem_leak_pseudo_rec1(11, 10, 0, &data));
#else
    printf("%i\n", mem_leak_pseudo_rec1(9, 8, 0, &data));
#endif

    return 1;
}
#endif
