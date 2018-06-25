#include <stdio.h>
#include <string.h>
#include "string_overflow.h"

void string_overflow_for_complex(int x) {
    char long_string[22] = "this is a long string";
    char short_string[13] = "short string";
    char* to_print = short_string;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    for(;;) {
        if(i > x) {
             to_print[13] = '?';  /* DANGER: x < 10 */
        } else {
             to_print[11] = '?';
        }
        if(i == 10) {
            to_print = long_string;
        }
        printf("val = %s\n", to_print);
        i++;
        if(i >= 20) {
            break;
        }
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_overflow_for_complex(10);
#else
    string_overflow_for_complex(9);
#endif

    return 1;
}
#endif
