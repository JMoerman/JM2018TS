#include <stdio.h>
#include <stdlib.h>
#include "zero_alloc.h"

void zero_alloc_do_while_continue(int x) {
    int* data;
    size_t size = 0;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    do {
        if(i == 8) {
            i++;
            continue;
        }
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
        i++;
    } while(i < 30);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    zero_alloc_do_while_continue(10);
#else
    zero_alloc_do_while_continue(9);
#endif

    return 1;
}
#endif
