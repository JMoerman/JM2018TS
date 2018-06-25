#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "refer_free.h"

void refer_free_if_else(bool a, bool b) {
    int* data;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    *data = 27;

    if(!a) {
        free(data);
    } else {
        (*data)++;
    }

    if(b) {
        val = 37;
    } else {
        val = *data; /* DANGER, if !a & !b */
    }

    if(a) {
        free(data);
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    refer_free_if_else(true, true);
    refer_free_if_else(true, false);
    refer_free_if_else(false, true);
#else
    refer_free_if_else(true, true); /* OK */
    refer_free_if_else(false, false); /* DANGER */
    refer_free_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif
