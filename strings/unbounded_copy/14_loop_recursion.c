#include <stdio.h>
#include <string.h>
#include "string_copy.h"

static char long_string[22] = "";
static char short_string[13] = "";

void string_copy_rec(int x, int i, char* to_print) {
    if(i <= 1) {
        printf("%s\n", to_print);
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        printf("%s\n", to_print);
        return;
    }
#endif

    if(i > x) {
        strcpy(to_print, "this is a long string");
    } else {
        strcpy(to_print, "short string");
    }

    if(i == 10) {
        to_print = short_string;
    }
    string_copy_rec(x, i-1, to_print);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_copy_rec(10, 20, long_string);
#else
    string_copy_rec(9, 20, long_string);
#endif

    return 1;
}
#endif
