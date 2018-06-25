#include "resource_leak.h"
#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void res_leak_cross_file(bool a, bool b) {
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

    conditional_close(file, a, 0);

    if(b & !a) {
        val = (int) fgetc(file);
        fclose(file);
    } else {
        val = 678;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_cross_file(true, true);
    res_leak_cross_file(true, false);
    res_leak_cross_file(false, true);
#else
    res_leak_cross_file(true, true); /* OK */
    res_leak_cross_file(false, false); /* DANGER */
    res_leak_cross_file(false, true); /* OK */
#endif
    return 1;
}
#endif
