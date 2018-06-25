#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "integer_overflow.h"

static void assign_int(int* dest, int int1, int int2, bool condition) {
    if(condition) {
        *dest = int1;
    } else {
        *dest = int2;
    }
}

void integer_overflow_function_pointer(bool a, bool b, void (*f)(int*, int, int, bool)) {
    int val;

#ifdef CATCH_BAD_PARAM
    if(!f || (!a & !b)) {
        return;
    }
#endif

    (*f)(&val, INT_MAX / 3 - 1, INT_MAX / 2 - 1, a);

    if(b) {
        printf("%i\n", val * 2 - 15);
    } else {
        printf("%i\n", val * 3 - 37); /* DANGER, if !a & !b */
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_function_pointer(true, true, &assign_int);
    integer_overflow_function_pointer(true, false, &assign_int);
    integer_overflow_function_pointer(false, true, &assign_int);
#else
    integer_overflow_function_pointer(true, true, &assign_int); /* OK */
    integer_overflow_function_pointer(false, false, &assign_int); /* DANGER */
    integer_overflow_function_pointer(false, true, &assign_int); /* OK */
#endif

    return 1;
}
#endif
