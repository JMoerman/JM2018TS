#include "refer_free.h"
#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void refer_free_cross_file(bool a, bool b) {
    int val;
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

    conditional_free((void*) data, !a, 0);

    if(b) {
        val = 678;
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
    refer_free_cross_file(true, true);
    refer_free_cross_file(true, false);
    refer_free_cross_file(false, true);
#else
    refer_free_cross_file(true, true); /* OK */
    refer_free_cross_file(false, false); /* DANGER */
    refer_free_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif
