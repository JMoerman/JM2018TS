#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "integer_overflow.h"

static void initialize_to_value(int arr[], int value, int length) {
    int i;

    for(i = 0; i < length; i++) {
        arr[i] = value;
    }
}

void integer_overflow_for_pointer(int x) {
    int arr[10];
    int* ptr;
    int i;

    if(x < 0 || x > 10) {
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x != 10) {
        return;
    }
#endif

    initialize_to_value(arr, INT_MAX, 10);

    ptr = arr;

    for(i = 0; i < x; i++, ptr++) {
        *ptr -= 20 + i;
    }

    ptr = arr;

    for(i = 0; i < 10; i++, ptr++) {
        printf("%i\n", *ptr + i);
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_for_pointer(10);
#else
    integer_overflow_for_pointer(9);
#endif

    return 1;
}
#endif
