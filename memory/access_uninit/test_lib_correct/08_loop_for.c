#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

void uninit_malloc_for(int x) {
    int* data;
    int val = 0;
    int i;

    if(x < 10) {
        return;
    }

    data = malloc(sizeof(int));
    if(!data) {
        return;
    }

    for(i = 0; i < 20; i++) {
        if(i > x) {
            val += 10 * (*data - 2); /* DANGER: x < 10 */
        } else {
            val += 10 * 4;
        }
        if(i == 10) {
            *data = 4;
            val += 10 * *data;
        }
    }

    printf("val = %i\n", val);
    free(data);
}

