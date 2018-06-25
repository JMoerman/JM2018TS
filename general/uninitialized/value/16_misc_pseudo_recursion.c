#include <stdio.h>
#include "uninitialized_value.h"

int uninit_val_pseudo_rec1(int x, int y, int i, int* ptr1, int* ptr2) {
    int uninit_val;
    int val;

    if(!ptr1) {
        return 0;
    }

#ifdef CATCH_BAD_PARAM
    if(!ptr2 && x <= 10 && x >= y) {
        return 0;
    }
#endif
    if(!ptr2) {
        ptr2 = &uninit_val;
    }

    if(i > 0) {
        return 37;
    }

    if(x < y) {
        *ptr2 = *ptr1;
    }

    val = uninit_val_pseudo_rec2(x, y, 1, ptr1, ptr2);
    ptr2 = 0;
    return 1 + val;
}

int uninit_val_pseudo_rec2(int x, int y, int i, int* ptr1, int* ptr2) {
    int* possibly_uninit;

    if(i <= 0) {
        return 3 * *ptr1 + uninit_val_pseudo_rec1(x, y, 1, ptr1, ptr2);
    }

    if(x > 10) {
        possibly_uninit = ptr1;
    } else {
        possibly_uninit = ptr2;
    }

    return 3 * *possibly_uninit;
}

#ifndef NO_MAIN
int main() {
    int init_val = 6;
    int uninit_val;
#ifdef NO_BUG
    printf("%i\n", uninit_val_pseudo_rec1(9, 10, 0, &init_val, &uninit_val));
    printf("%i\n", uninit_val_pseudo_rec1(10, 10, 0, &init_val, &init_val));
    printf("%i\n", uninit_val_pseudo_rec1(11, 10, 0, &init_val, &uninit_val));
#else
    printf("%i\n", uninit_val_pseudo_rec1(10, 10, 0, &init_val, &uninit_val));
#endif

    return 1;
}
#endif
