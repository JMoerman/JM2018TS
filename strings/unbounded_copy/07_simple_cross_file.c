#include "string_copy.h"
#include "common.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void string_copy_cross_file(bool a, bool b) {
    char long_string[22];
    char short_string[13];
    char* to_print;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    to_print = (char*) choose_pointer((void*) long_string, (void*) short_string, a);

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
    string_copy_cross_file(true, true);
    string_copy_cross_file(true, false);
    string_copy_cross_file(false, true);
#else
    string_copy_cross_file(true, true); /* OK */
    string_copy_cross_file(false, false); /* DANGER */
    string_copy_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif
