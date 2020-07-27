#include "integer_overflow.h"
#include "common.h"
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

void integer_overflow_cross_file(bool a, bool b) {
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    val = choose_int (INT_MAX / 3 - 1, INT_MAX / 2 - 1, a);

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
    integer_overflow_cross_file(true, true);
    integer_overflow_cross_file(true, false);
    integer_overflow_cross_file(false, true);
#else
    integer_overflow_cross_file(true, true); /* OK */
    integer_overflow_cross_file(false, false); /* DANGER */
    integer_overflow_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif
