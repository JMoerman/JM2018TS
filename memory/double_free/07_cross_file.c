#include "double_free.h"
#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void double_free_cross_file(bool a, bool b) {
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
        if (a) {
            free(data);
        }
    } else {
        free(data); /* DANGER, if !a & !b */
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_cross_file(true, true);
    double_free_cross_file(true, false);
    double_free_cross_file(false, true);
#else
    double_free_cross_file(true, true); /* OK */
    double_free_cross_file(false, false); /* DANGER */
    double_free_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif
