#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

void uninit_malloc_for_array(int x) {
    int* data;
    int p[20];
    int val = 0, i = 0;

    if(x < 0 || x > 19) {
        return;
    }

    if(x != 19) {
        return;
    }

    data = malloc(sizeof(int));
    if(!data) {
        return;
    }

    *data = 12;

    for(i = 0; i < 20; i++) {
        p[i] = 0;
    }
    p[x] = 1;

    for(i = 0; i < 20; i++) {
        if(p[i] == 1) {
            free(data);
            data = malloc(sizeof(int));
            if(!data) {
                return;
            }
        } else {
            val += *data; /* DANGER: x < 19 */
        }
    }

    printf("%i\n", val);
    free(data);
}

