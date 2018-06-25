#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

int uninit_malloc_pseudo_rec1(int x, int y, int i, int* ptr1, int* ptr2) {
    int *data;

    if(i > 0) {
        return 37;
    }

    if(!ptr1) {
        ptr1 = malloc(sizeof(int));
        if(ptr1) {
            *ptr1 = 1;
        } else {
            if(ptr2) {
                free(ptr2);
            }
            return -1;
        }
    }
    if(!ptr2) {
        ptr2 = malloc(sizeof(int));
        if(!ptr2) {
            free(ptr1);
            return -1;
        }
    }

    if(x < y) {
        *ptr2 = *ptr1;
    }

    return uninit_malloc_pseudo_rec2(x, y, 1, ptr1, ptr2);
}

int uninit_malloc_pseudo_rec2(int x, int y, int i, int* ptr1, int* ptr2) {
    int val;

    if(i <= 0) {
        return 3 * (*ptr1) + uninit_malloc_pseudo_rec1(x, y, 1, ptr1, ptr2);
    }

    if(x > 10) {
        val = *ptr1;
    } else {
        val = *ptr2;
    }

    free(ptr1);
    free(ptr2);

    return 3 * val;
}

int main() {
    int* initialized = malloc(sizeof(int));
    printf("%i\n", uninit_malloc_pseudo_rec1(9, 10, 0, 0, 0));
    if(initialized) {
        *initialized = 2;
        printf("%i\n", uninit_malloc_pseudo_rec1(10, 10, 0, 0, initialized));
    }
    printf("%i\n", uninit_malloc_pseudo_rec1(11, 10, 0, 0, 0));

    return 1;
}
