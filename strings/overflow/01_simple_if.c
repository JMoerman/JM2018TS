#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "string_overflow.h"

void string_overflow_if_else(bool a, bool b) {
    char long_string[] = "this is a long string";
    char short_string[] = "short string";
    char* to_print;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    if(a) {
        to_print = long_string;
    } else {
        to_print = short_string;
    }

    if(b) {
        to_print[11] = '?';
    } else {
        to_print[13] = '?';
    }

    printf("%s\n", to_print);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_overflow_if_else(true, true);
    string_overflow_if_else(true, false);
    string_overflow_if_else(false, true);
#else
    string_overflow_if_else(true, true); /* OK */
    string_overflow_if_else(false, false); /* DANGER */
    string_overflow_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif
