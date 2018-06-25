#include "string_copy.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static char* choose_string(char* string1, char* string2, bool condition) {
    if(condition) {
        return string1;
    } else {
        return string2;
    }
}

static void conditional_copy(char* destination, char* source1, char* source2, bool condition) {
    if(condition) {
        strcpy(destination, source1);
    } else {
        strcpy(destination, source2);
    }
}

void string_copy_if_else_multi(bool a, bool b) {
    char long_string[22];
    char short_string[13];
    char* to_print;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    to_print = choose_string(long_string, short_string, a);

    conditional_copy(to_print, "short string", "this is a long string", b); /* DANGER, if !a & !b */

    printf("%s\n", to_print);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_copy_if_else_multi(true, true);
    string_copy_if_else_multi(true, false);
    string_copy_if_else_multi(false, true);
#else
    string_copy_if_else_multi(true, true); /* OK */
    string_copy_if_else_multi(false, false); /* DANGER */
    string_copy_if_else_multi(false, true); /* OK */
#endif
    return 1;
}
#endif
