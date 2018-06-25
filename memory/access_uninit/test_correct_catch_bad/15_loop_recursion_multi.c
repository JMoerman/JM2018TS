#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

int uninit_malloc_rec_decr(int x, int i, int* ptr1, int* ptr2) {
    if(i <= 1) {
        return 0;
    }

    return uninit_malloc_rec_multi(x, i-1, ptr1, ptr2);
}

int uninit_malloc_rec_multi(int x, int i, int* ptr1, int* ptr2) {
    int val;

    if(i <= 1) {
        free(ptr1);
        free(ptr2);
        return 0;
    }

    if(!ptr2) {
        if((x > 0 && i < 10) || (i >= 10 && x > 10)) {
            return uninit_malloc_rec(x, i-1, ptr1, ptr1);
        }
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
        return 2 * *ptr1 + uninit_malloc_rec_decr(x, i, ptr1, ptr2);
    }

    if(i < x) {
        val = *ptr2;
    } else {
        val = *ptr1;
    }
    if(i == 10) {
        *ptr2 = *ptr1;
    }
    return uninit_malloc_rec_decr(x, i, ptr1, ptr2) + 3 * val;
}

int main() {
    int* initialized = malloc(sizeof(int));;
    printf("%i\n", uninit_malloc_rec_multi(10, 20, 0, 0));
    if(initialized) {
        *initialized = 2;
        printf("%i\n", uninit_malloc_rec_multi(11, 20, 0, initialized));
    }

    return 1;
}
