#include <stdio.h>
#include <stdbool.h>
#include "divide_by_zero.h"

static void assign_int(int* dest, int int1, int int2, bool condition) {
    if(condition) {
        *dest = int1;
    } else {
        *dest = int2;
    }
}

void divide_zero_pass_by_reference(bool a, bool b) {
    int divisor;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    assign_int(&divisor, 2, 0, a);

    if(b) {
        val = 25 / 4;
    } else {
        val = 91 / divisor; /* DANGER, if !a & !b */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    divide_zero_pass_by_reference(true, true);
    divide_zero_pass_by_reference(true, false);
    divide_zero_pass_by_reference(false, true);
#else
    divide_zero_pass_by_reference(true, true); /* OK */
    divide_zero_pass_by_reference(false, false); /* DANGER */
    divide_zero_pass_by_reference(false, true); /* OK */
#endif

    return 1;
}
#endif
