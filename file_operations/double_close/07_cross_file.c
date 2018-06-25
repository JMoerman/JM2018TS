#include "double_close.h"
#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void double_close_cross_file(bool a, bool b) {
    int val;
    FILE* file;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif
    file = fopen("file.txt","r");

    if(!file) {
        return;
    }

    val = (int) fgetc(file);

    conditional_close(file, !a, 0);

    if(b) {
        val = 678;
    } else {
        fclose(file);
    }

    if(a & b) {
        fclose(file);
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_close_cross_file(true, true);
    double_close_cross_file(true, false);
    double_close_cross_file(false, true);
#else
    double_close_cross_file(true, true); /* OK */
    double_close_cross_file(false, false); /* DANGER */
    double_close_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif
