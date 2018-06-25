#include <stdio.h>
#include "nullpointer.h"

int nullpointer_rec_decr(int x, int i, int* ptr1, int* ptr2) {
    if(i <= 1) {
        return 0;
    }

    return nullpointer_rec_multi(x, i-1, ptr1, ptr2);
}

int nullpointer_rec_multi(int x, int i, int* ptr1, int* ptr2) {
    int val = 0;
    int* ptr;

    if(!ptr1 || !ptr2) { /* Signal the tools that these can be null (for -DNO_MAIN) */
        val++;
    }

#ifdef CATCH_BAD_PARAM
    if(!ptr1 && (!ptr2 || i >= x || i >= 10)) {
        return -1;
    }
    if(!ptr2 && (x > 2 || (i > 10 && x > 10))) {
        return nullpointer_rec(x, i-1, ptr1, ptr1);
    }
#endif

    if(i < x) {
        ptr = ptr2;
    } else {
        ptr = ptr1;
    }
    if(i == 10) {
        ptr2 = ptr1;
    }
    return val + *ptr + nullpointer_rec_decr(x, i, ptr1, ptr2);
}



#ifndef NO_MAIN
int main() {
    int arr[3] = {1, 2, 3};
#ifdef NO_BUG
    printf("%i", nullpointer_rec_multi(10, 20, arr, 0));
#else
    printf("%i", nullpointer_rec_multi(11, 20, arr, 0));
#endif

    return 1;
}
#endif
