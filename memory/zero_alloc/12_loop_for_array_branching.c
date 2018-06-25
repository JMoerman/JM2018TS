#include <stdio.h>
#include <stdlib.h>
#include "zero_alloc.h"

void zero_alloc_for_array(int x) {
    int* data;
    size_t size;
    int p[20];
    int i;

#ifdef CATCH_BAD_PARAM
    if(x != 19) {
        return;
    }
#endif

    size = sizeof(int);

    for(i = 0; i < 20; i++) {
        p[i] = 0;
    }
    p[x] = 1;

    for(i = 0; i < 20; i++) {
        if(p[i] == 1) {
            size -= sizeof(int);
        } else {
            data = malloc(size); /* DANGER: x < 19 */
            if(!data) {
                break;
            }
            *data = i;
            printf("%i\n", *data);
            free(data);
        }
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    zero_alloc_for_array(19);
#else
    zero_alloc_for_array(10);
#endif

    return 1;
}
#endif
