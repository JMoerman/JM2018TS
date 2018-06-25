#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "memory_leak.h"

void mem_leak_if_else(bool a, bool b) {
    int* data;
    int val = 0;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    *data = 27;

    if(a) {
        val = *data;
        free(data);
    } else {
        (*data)++;
    }

    if(b & !a) {
        val = *data;
        free(data);
    } else {
        val += 37;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    mem_leak_if_else(true, true);
    mem_leak_if_else(true, false);
    mem_leak_if_else(false, true);
#else
    mem_leak_if_else(true, true); /* OK */
    mem_leak_if_else(false, false); /* DANGER */
    mem_leak_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif
