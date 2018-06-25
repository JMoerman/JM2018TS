#include <stdio.h>
#include "nullpointer.h"

void nullpointer_while_continue(int x) {
    int arr[3] = {1, 2, 3};
    int* ptr = 0;
    int val = 0, i = 0;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    while(i < 30) {
        if(i > x) {
            val += *ptr; /* DANGER: x < 10 */
        } else {
            val += arr[0];
        }
        if(i == 10) {
            ptr = arr;
            val += *ptr;
        }
        i++;
        if(i < 20) {
            continue;
        }
    }

    printf("val = %i", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    nullpointer_while_continue(10);
#else
    nullpointer_while_continue(9);
#endif

    return 1;
}
#endif
