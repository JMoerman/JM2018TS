#include <stdio.h>
#include <string.h>
#include "string_copy.h"

void string_copy_goto(int x) {
    char short_string[] = "Short string";
    char* to_print = "Default string content";
    int i;

#ifdef CATCH_BAD_PARAM
    if(x > 0) {
        return;
    }
#endif

    i = 0;

GOTO_LABEL:
    if(i <= x) {
        strcpy(to_print, "this is a long string");
    } else {
        printf("%s\n", to_print);
    }

    to_print = short_string;

    if(i == 0) {
        i++;
        goto GOTO_LABEL;
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_copy_goto(0);
#else
    string_copy_goto(1);
#endif

    return 1;
}
#endif
