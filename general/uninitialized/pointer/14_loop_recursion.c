#include <stdio.h>
#include "uninit_ptr.h"

int uninit_ptr_rec(int x, int i, int** ptr1, int** ptr2) {
    int** ptr;
    int* uninit;

    if(i <= 1 || !ptr1) {
        return 0;
    }

#ifdef CATCH_BAD_PARAM
    if(!ptr2 && ((i < 10 && x > 2) || (i >= 10 && x > 10))) {
         return uninit_ptr_rec(x, i-1, ptr1, ptr1);
    }
#endif
    if(!ptr2) {
        ptr2 = &uninit;
    }

    if(i < x) {
        ptr = ptr2;
    } else {
        ptr = ptr1;
    }
    if(i == 10) {
        return **ptr + uninit_ptr_rec(x, i-1, ptr1, ptr1);
    }
    return **ptr + uninit_ptr_rec(x, i-1, ptr1, ptr2);
}

#ifndef NO_MAIN
int main() {
    int arr[3] = {1, 2, 3};
    int* arr_allias = arr;
    int* uninit;
#ifdef NO_BUG
    int* arr_allias2 = arr+1;
    printf("%i\n", uninit_ptr_rec(10, 20, &arr_allias, &uninit));
    printf("%i\n", uninit_ptr_rec(11, 20, &arr_allias, &arr_allias2));
#else
    printf("%i\n", uninit_ptr_rec(11, 20, &arr_allias, &uninit));
#endif

    return 1;
}
#endif
