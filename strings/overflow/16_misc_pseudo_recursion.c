#include <stdio.h>
#include <string.h>
#include "string_overflow.h"

static char long_string[22] = "";
static char short_string[13] = "";

void string_overflow_pseudo_rec1(int x, int y, int i, char* to_print) {

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x >= y) {
        return;
    }
#endif

    if(i > 0) {
        return;
    }

    if(x > 10) {
        if(!to_print) {
            to_print = long_string;
        }
    } else {
        to_print = short_string;
    }

    string_overflow_pseudo_rec2(x, y, 1,to_print);
}

void string_overflow_pseudo_rec2(int x, int y, int i, char* to_print) {
    if(i > 0) {
        if(x < y) {
            to_print[11] = '?';
        } else {
            to_print[13] = '?';
        }
        printf("%s\n", to_print);
    } else {
        string_overflow_pseudo_rec1(x, y, 1, to_print);
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_overflow_pseudo_rec1(9, 10, 0, 0);
    string_overflow_pseudo_rec1(11, 10, 0, 0);
#else
    string_overflow_pseudo_rec1(10, 10, 0, 0);
#endif

    return 1;
}
#endif
