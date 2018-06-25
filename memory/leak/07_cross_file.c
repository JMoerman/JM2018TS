#include "memory_leak.h"
#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void mem_leak_cross_file(bool a, bool b) {
    int val;
    int* data;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif
    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    conditional_free((void*) data, !a, 0);

    if(b & a) {
        val = *data;
        free(data);
    } else {
        val = 678;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    mem_leak_cross_file(true, true);
    mem_leak_cross_file(true, false);
    mem_leak_cross_file(false, true);
#else
    mem_leak_cross_file(true, true); /* OK */
    mem_leak_cross_file(false, false); /* DANGER */
    mem_leak_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif
