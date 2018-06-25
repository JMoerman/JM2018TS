#include <stdio.h>
#include <string.h>
#include "string_overflow.h"

static char long_string[22] = "";
static char short_string[13] = "";

void string_overflow_rec_decr(int x, int i, char* to_print) {
    if(i <= 1) {
        printf("%s\n", to_print);
        return;
    }

    string_overflow_rec_multi(x, i-1, to_print);
}

void string_overflow_rec_multi(int x, int i, char* to_print) {
#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        printf("%s\n", to_print);
        return;
    }
#endif

    if(i > x) {
        to_print[13] = '?';
    } else {
        to_print[11] = '?';
    }

    if(i == 10) {
        to_print = short_string;
    }
    string_overflow_rec_decr(x, i, to_print);
}



#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_overflow_rec_multi(10, 20, long_string);
#else
    string_overflow_rec_multi(11, 20, long_string);
#endif

    return 1;
}
#endif
