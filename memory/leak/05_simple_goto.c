#include <stdio.h>
#include <stdlib.h>
#include "memory_leak.h"

void mem_leak_goto(int x) {
    int* data = 0;
    int val = 0;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x > 0) {
        return;
    }
#endif

GOTO_LABEL:
    if(i <= x) {
        data = malloc(5*sizeof(int));

        if(!data) {
            return;
        }

        *data = 7698;
        val += *data;
    } else {
        printf("%i\n", val);
    }

    if(i == 0 && data) {
        i++;
        free(data);
        goto GOTO_LABEL;
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    mem_leak_goto(0);
#else
    mem_leak_goto(1);
#endif

    return 1;
}
#endif
