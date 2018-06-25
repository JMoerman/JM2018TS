#include "uninitialized_malloc.h"
#include <stdlib.h>

int uninit_malloc_switch(int x, int y) {
    int* data;
    int val;

    if((x == 10 || x == 5) && x >= y) {
        return -1;
    }
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

int main() {
    uninit_malloc_switch(5, 11);
    uninit_malloc_switch(10, 11);
    uninit_malloc_switch(11, 11);
    uninit_malloc_switch(7, 5);

    return 1;
}
