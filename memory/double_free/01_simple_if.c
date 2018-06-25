#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_free.h"

void double_free_if_else(bool a, bool b) {
    int* data;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    if(!a) {
        free(data);
    }

    if(b) {
        if(a) {
            free(data);
        }
    } else {
        free(data); /* DANGER, if !a & !b */
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_if_else(true, true);
    double_free_if_else(true, false);
    double_free_if_else(false, true);
#else
    double_free_if_else(true, true); /* OK */
    double_free_if_else(false, false); /* DANGER */
    double_free_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif
