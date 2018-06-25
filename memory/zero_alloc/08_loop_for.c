#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "zero_alloc.h"

void zero_alloc_for(int x) {
    int* data;
    size_t size = 0;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    for(i = 0; i < 20; i++) {
        if(i > x) {
            data = malloc(size); /* DANGER: x < 10 */
        } else {
            data = malloc(size + sizeof(int));
        }

        if(data) {
            *data = i;
            printf("%i\n", *data);
            free(data);
        }

        if(i == 10) {
            size += sizeof(int);
        }
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    zero_alloc_for(10);
#else
    zero_alloc_for(9);
#endif

    return 1;
}
#endif
