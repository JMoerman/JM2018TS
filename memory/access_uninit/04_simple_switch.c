#include "uninitialized_malloc.h"
#include <stdlib.h>

int uninit_malloc_switch(int x, int y) {
    int* data;
    int val;

#ifdef CATCH_BAD_PARAM
    if((x == 10 || x == 5) && x >= y) {
        return -1;
    }
#endif
    data = malloc(sizeof(int));
    if(!data) {
        return -1;
    }

    if(x < y) {
        *data = 1;
    }

    switch (x) {
        case 5: {
            val = 37 * *data; /* DANGER: x >= y */
            break;
        }
        case 7: {
            val = -37 * 2;
            break;
        }
        case 10: {
            val = 73 * *data; /* DANGER: x >= y */
            break;
        }
        case 12: {
            val = 73 * 5;
            break;
        }
        default: {
            val = 100 * 8;
            break;
        }
    };

    free(data);

    return val;
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_malloc_switch(5, 11);
    uninit_malloc_switch(10, 11);
    uninit_malloc_switch(11, 11);
    uninit_malloc_switch(7, 5);
#else
    uninit_malloc_switch(5, 10); /* OK */
    uninit_malloc_switch(10, 10); /* DANGER */
    uninit_malloc_switch(11, 10); /* OK */
    uninit_malloc_switch(7, 5); /* OK */
#endif

    return 1;
}
#endif
