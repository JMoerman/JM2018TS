#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "string_copy.h"

void string_copy_if_else(bool a, bool b) {
    char long_string[22];
    char short_string[13];
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
        strcpy(to_print, "short string");
    } else {
        strcpy(to_print, "this is a long string");
    }

    printf("%s\n", to_print);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_copy_if_else(true, true);
    string_copy_if_else(true, false);
    string_copy_if_else(false, true);
#else
    string_copy_if_else(true, true); /* OK */
    string_copy_if_else(false, false); /* DANGER */
    string_copy_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif
