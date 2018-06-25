#include <stdio.h>
#include "uninitialized_value.h"

int uninit_val_rec_decr(int x, int i, int* ptr1, int* ptr2) {
    if(i <= 1) {
        return 0;
    }

    return uninit_val_rec_multi(x, i-1, ptr1, ptr2);
}

int uninit_val_rec_multi(int x, int i, int* ptr1, int* ptr2) {
    int* possibly_uninit;
    int uninit_val;

    if(i <= 1 || !ptr1) {
        return 0;
    }

#ifdef CATCH_BAD_PARAM
    if(!ptr2 && ((i < 10 && x > 2) || (i >= 10 && x > 10))) {
         return 0;
    }
#endif
    if(!ptr2) {
        ptr2 = &uninit_val;
    }

    if(i < x) {
        possibly_uninit = ptr2;
    } else {
        possibly_uninit = ptr1;
    }
    if(i == 10) {
        *ptr2 = *ptr1;
    }
    return 3 * *possibly_uninit + uninit_val_rec_decr(x, i, ptr1, ptr2);
}

#ifndef NO_MAIN
int main() {
    int init_val = 6;
    int uninit_val;
#ifdef NO_BUG
    printf("%i", uninit_val_rec_multi(10, 20, &init_val, &uninit_val));
#else
    printf("%i", uninit_val_rec_multi(11, 20, &init_val, &uninit_val));
#endif

    return 1;
}
#endif
