#include <stdio.h>
#include <stdlib.h>
#include "zero_alloc.h"

void zero_alloc_for_complex(int x) {
    int* data;
    size_t size = 0;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    for(;;) {
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
        if(i >= 20) {
            break;
        }
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    zero_alloc_for_complex(10);
#else
    zero_alloc_for_complex(9);
#endif

    return 1;
}
#endif
