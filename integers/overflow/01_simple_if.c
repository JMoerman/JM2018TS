#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "integer_overflow.h"

void integer_overflow_if_else(bool a, bool b) {
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    if(a) {
        val = INT_MAX / 3 - 1;
    } else {
        val = INT_MAX / 2 - 1;
    }

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
    integer_overflow_if_else(true, true);
    integer_overflow_if_else(true, false);
    integer_overflow_if_else(false, true);
#else
    integer_overflow_if_else(true, true); /* OK */
    integer_overflow_if_else(false, false); /* DANGER */
    integer_overflow_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif
