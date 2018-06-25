#include <stdio.h>
#include "nullpointer.h"

void nullpointer_goto(int x) {
    int arr[3] = {1, 2, 3};
    int* ptr = arr;
    int val, i;

#ifdef CATCH_BAD_PARAM
    if(x > 0) {
        return;
    }
#endif

    val = *(ptr+1);
    i = 0;

GOTO_LABEL:
    if(i <= x) {
        val += *ptr;
    } else {
        printf("%i\n", val);
    }

    ptr = 0;

    if(i == 0) {
        i++;
        goto GOTO_LABEL;
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    nullpointer_goto(0);
#else
    nullpointer_goto(1);
#endif

    return 1;
}
#endif
