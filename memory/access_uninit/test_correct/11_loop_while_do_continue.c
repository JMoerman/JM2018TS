#include <stdio.h>
#include <stdlib.h>
#include "uninitialized_malloc.h"

void uninit_malloc_do_while_continue(int x) {
    int* data;
    int val = 0, i = 0;


    data = malloc(sizeof(int));
    if(!data) {
        return;
    }

    do {
        if(i > x) {
            val += 10 * (*data - 2); /* DANGER: x < 10 */
        } else {
            val += 10 * 4;
        }
        if(i == 10) {
            *data = 4;
            val += 10 * *data;
        }
        i++;
        if(i < 20) {
            continue;
        }
    } while(i < 30);

    printf("val = %i", val);
    free(data);
}

int main() {
    uninit_malloc_do_while_continue(10);

    return 1;
}
