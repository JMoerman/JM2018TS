#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

void uninit_malloc_goto(int x) {
    int val = 0, i = 0;
    int* data;


    data = malloc(sizeof(int));

    if(!data) {
        return;
    }

    *data = x;

GOTO_LABEL:
    if(i <= x) {
        if(data) {
            val += *data;
        }
    } else {
        printf("%i\n", val);
    }

    free(data);
    data = malloc(sizeof(int));

    if(i == 0) {
        i++;
        goto GOTO_LABEL;
    }

    free(data);
}

int main() {
    uninit_malloc_goto(1);

    return 1;
}
