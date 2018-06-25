#include "string_overflow.h"
#include <string.h>
#include <stdio.h>

void string_overflow_switch(int x, int y) {
    char long_string[22] = "this is a long string";
    char short_string[13] = "short string";
    char* to_print;

#ifdef CATCH_BAD_PARAM
    if((x == 10 || x == 5) && x >= y) {
        return -1;
    }
#endif

    if(x < y) {
        to_print = long_string;
    } else {
        to_print = short_string;
    }

    switch (x) {
        case 5: {
            to_print[13] = '?'; /* DANGER: x >= y */
            break;
        }
        case 7: {
            to_print[11] = '?';
            break;
        }
        case 10: {
            to_print[15] = '?'; /* DANGER: x >= y */
            break;
        }
        case 12: {
            to_print[8] = '?';
            break;
        }
        default: {
            to_print[0] = '?';
            break;
        }
    };

    printf("%s\n", to_print);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_overflow_switch(5, 11);
    string_overflow_switch(10, 11);
    string_overflow_switch(11, 11);
    string_overflow_switch(7, 5);
#else
    string_overflow_switch(5, 10); /* OK */
    string_overflow_switch(10, 10); /* DANGER */
    string_overflow_switch(11, 10); /* OK */
    string_overflow_switch(7, 5); /* OK */
#endif

    return 1;
}
#endif
