#include <stdio.h>
#include <stdlib.h>
#include "memory_leak.h"

void mem_leak_if_else_int2(int x, int y) {
    int* data;
    int val = 0;
    int m, n;

    m = -1;
    n = 5;

    x = x*m+n;

#ifdef CATCH_BAD_PARAM
    if(x > 10 && x < y) {
        return;
    }
#endif

    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    *data = 27;

    if(x <= 10) {
        val = *data;
        free(data);
    } else {
        (*data)++;
    }

    if(x >= y) {
        if(x > 10) {
            val = *data * 2;
            free(data);
        }
    } else {
        val += 10;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    mem_leak_if_else_int2(-5, 10);
    mem_leak_if_else_int2(-5, 11);
    mem_leak_if_else_int2(-6, 11);
#else
    mem_leak_if_else_int2(-5, 10); /* OK */
    mem_leak_if_else_int2(-6, 12); /* DANGER */
    mem_leak_if_else_int2(-6, 11); /* OK */
#endif

    return 1;
}
#endif
