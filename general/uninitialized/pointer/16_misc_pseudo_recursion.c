#include <stdio.h>
#include "uninit_ptr.h"

int uninit_ptr_pseudo_rec1(int x, int y, int i, int** ptr1, int** ptr2) {
    int* uninit;
#ifdef CATCH_BAD_PARAM
    if(!ptr2 && x <= 10 && x >= y) {
        return 0;
    }
#endif
    if(!ptr2) {
        ptr2 = &uninit;
    }

    if(i > 0) {
        return 37;
    }

    if(x < y) {
        ptr2 = ptr1;
    }

    return uninit_ptr_pseudo_rec2(x, y, 1, ptr1, ptr2);
}

int uninit_ptr_pseudo_rec2(int x, int y, int i, int** ptr1, int** ptr2) {
    int** ptr;

    if(i > 0) {
        return **ptr1 + uninit_ptr_pseudo_rec1(x, y, 1, ptr1, ptr2);
    }

    if(x > 10) {
        ptr = ptr1;
    } else {
        ptr = ptr2;
    }

    return **ptr;
}

#ifndef NO_MAIN
int main() {
    int arr[3] = {1, 2, 3};
    int* arr_allias = arr;
    int* uninit;
#ifdef NO_BUG
    int* arr_allias2 = arr+1;
    printf("%i\n", uninit_ptr_pseudo_rec1(9, 10, 0, &arr_allias, &uninit));
    printf("%i\n", uninit_ptr_pseudo_rec1(10, 10, 0, &arr_allias, &arr_allias2));
    printf("%i\n", uninit_ptr_pseudo_rec1(11, 10, 0, &arr_allias, &uninit));
#else
    printf("%i\n", uninit_ptr_pseudo_rec1(10, 10, 0, &arr_allias, &uninit));
#endif

    return 1;
}
#endif
