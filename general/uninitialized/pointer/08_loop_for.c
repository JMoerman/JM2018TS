#include <stdio.h>
#include "uninit_ptr.h"

void uninit_ptr_for(int x) {
    int arr[3] = {1, 2, 3};
    int* ptr;
    int val = 0;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    for(i = 0; i < 20; i++) {
        if(i > x) {
            val += *ptr; /* DANGER: x < 10 */
        } else {
            val += arr[0];
        }
        if(i == 10) {
            ptr = arr;
            val += *ptr;
        }
    }

    printf("val = %i", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_ptr_for(10);
#else
    uninit_ptr_for(9);
#endif

    return 1;
}
#endif
