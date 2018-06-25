#include <stdio.h>
#include "nullpointer.h"

void nullpointer_for_array(int x) {
    int p[20];
    int* ptr = p;
    int val = 0, i = 0;

#ifdef CATCH_BAD_PARAM
    if(x != 19) {
        return;
    }
#endif

    for(i = 0; i < 20; i++) {
        p[i] = 0;
    }
    p[x] = 1;

    for(i = 0; i < 20; i++) {
        if(p[i] == 1) {
            ptr = 0;
        } else {
            val = *ptr; /* DANGER: x < 19 */
        }
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    nullpointer_for_array(19);
#else
    nullpointer_for_array(10);
#endif

    return 1;
}
#endif
