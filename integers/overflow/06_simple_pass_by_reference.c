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

void integer_overflow_pass_by_reference(bool a, bool b) {
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    assign_int(&val, INT_MAX / 3 - 1, INT_MAX / 2 - 1, a);

    if(b) {
        val = val * 2;
    } else {
        val = val * 3; /* DANGER if !a */
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    integer_overflow_pass_by_reference(true, true);
    integer_overflow_pass_by_reference(true, false);
    integer_overflow_pass_by_reference(false, true);
#else
    integer_overflow_pass_by_reference(true, true); /* OK */
    integer_overflow_pass_by_reference(false, false); /* DANGER */
    integer_overflow_pass_by_reference(false, true); /* OK */
#endif

    return 1;
}
#endif
