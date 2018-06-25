#include <stdlib.h>
#include <stdio.h>
#include "divide_by_zero.h"

static void initialize_to_zero(int arr[], int length) {
    int i;

    for(i = 0; i < length; i++) {
        arr[i] = 0;
    }
}

void divide_zero_for_pointer(int x) {
    int divisors[10];
    int* ptr;
    int val = 0, i;

    if(x < 0 || x > 10) {
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x != 10) {
        return;
    }
#endif

    initialize_to_zero(divisors, 10);

    for(i = 0, ptr = divisors; i < x; i++, ptr++) {
        *ptr = i + 1;
    }

    for(i = 0, ptr = divisors; i <= 9; i++, ptr++) {
        val += 100 / (*ptr);
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    divide_zero_for_pointer(10);
#else
    divide_zero_for_pointer(9);
#endif

    return 1;
}
#endif
