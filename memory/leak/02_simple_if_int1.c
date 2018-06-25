#include <stdio.h>
#include <stdlib.h>
#include "memory_leak.h"

void mem_leak_if_else_int1(int x, int y) {
    int val = 0;
    int* data;

#ifdef CATCH_BAD_PARAM
    if(x <= 10 && x < y) {
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
    mem_leak_if_else_int1(10, 10);
    mem_leak_if_else_int1(10, 11);
    mem_leak_if_else_int1(11, 11);
#else
    mem_leak_if_else_int1(10, 10); /* OK */
    mem_leak_if_else_int1(11, 12); /* DANGER */
    mem_leak_if_else_int1(11, 11); /* OK */
#endif

    return 1;
}
#endif
