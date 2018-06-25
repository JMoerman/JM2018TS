#include <stdio.h>
#include "nullpointer.h"

int nullpointer_pseudo_rec1(int x, int y, int i, int* ptr1, int* ptr2) {
    int val = 0;

    if(!ptr1 || !ptr2) { /* Signal the tools that these can be null (for -DNO_MAIN) */
        val++;
    }

#ifdef CATCH_BAD_PARAM
    if(!ptr1 && (x < y || x > 10)) {
        return -1;
    }
    if(!ptr2 && x >= y && x <= 10) {
        return -1;
    }
#endif

    if(i > 0) {
        return 37;
    }

    if(x < y) {
        ptr2 = ptr1;
    }

    return val + nullpointer_pseudo_rec2(x, y, 1, ptr1, ptr2);
}

int nullpointer_pseudo_rec2(int x, int y, int i, int* ptr1, int* ptr2) {
    int* ptr;

    if(i <= 0) {
        return *ptr1 + nullpointer_pseudo_rec1(x, y, 1, ptr1, ptr2);
    }

    if(x > 10) {
        ptr = ptr1;
    } else {
        ptr = ptr2;
    }

    return *ptr;
}

#ifndef NO_MAIN
int main() {
    int arr[3] = {1, 2, 3};
#ifdef NO_BUG
    printf("%i\n", nullpointer_pseudo_rec1(9, 10, 0, arr, 0));
    printf("%i\n", nullpointer_pseudo_rec1(10, 10, 0, arr, arr+1));
    printf("%i\n", nullpointer_pseudo_rec1(11, 10, 0, arr, 0));
#else
    printf("%i\n", nullpointer_pseudo_rec1(10, 10, 0, arr, 0));
#endif

    return 1;
}
#endif
