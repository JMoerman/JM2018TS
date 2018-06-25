#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "memory_leak.h"

int mem_leak_rec(int x, int i, int* data, bool do_free) {
    int val;

    if(i <= 1) {
        return 0;
    }

#ifdef CATCH_BAD_PARAM
    if(!do_free && (x > 10 || i < 10)) {
        return -1;
    }
#endif

    if(i < x) {
        if(!data) data = malloc(sizeof(int));
        if(!data) return -1;
        *data = i;
        val = *data;
        if(do_free) {
            free(data);
            data = 0;
        }
    } else {
        if(data) {
            val = *data / 2;
        } else {
            val = 8;
        }
    }
    if(i == 10) {
        do_free = true;
    }

    return val + mem_leak_rec(x, i-1, data, do_free);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    printf("%i\n", mem_leak_rec(10, 20, 0, false));
    printf("%i\n", mem_leak_rec(11, 20, 0, true));
#else
    printf("%i\n", mem_leak_rec(11, 20, 0, false));
#endif

    return 1;
}
#endif
