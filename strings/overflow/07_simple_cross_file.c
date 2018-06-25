#include "string_overflow.h"
#include "common.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void string_overflow_cross_file(bool a, bool b) {
    char long_string[22] = "this is a long string";
    char short_string[13] = "short string";
    char* to_print;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    to_print = (char*) choose_pointer((void*) long_string, (void*) short_string, a);

    if(b) {
        to_print[11] = '?';
    } else {
        to_print[13] = '?'; /* DANGER if !a */
    }

    printf("%s\n", to_print);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_overflow_cross_file(true, true);
    string_overflow_cross_file(true, false);
    string_overflow_cross_file(false, true);
#else
    string_overflow_cross_file(true, true); /* OK */
    string_overflow_cross_file(false, false); /* DANGER */
    string_overflow_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif
