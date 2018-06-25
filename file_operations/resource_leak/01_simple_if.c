#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "resource_leak.h"

void res_leak_if_else(bool a, bool b) {
    FILE* file;
    int val = 0;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    file = fopen("file.txt","r");

    if(!file) {
        return;
    }

    if(a) {
        val = (int) fgetc(file);
        fclose(file);
    } else {
        val = ((int) fgetc(file)) * 2;
    }

    if(b & !a) {
        val += (int) fgetc(file);
        fclose(file);
    } else {
        val += 37;
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_if_else(true, true);
    res_leak_if_else(true, false);
    res_leak_if_else(false, true);
#else
    res_leak_if_else(true, true); /* OK */
    res_leak_if_else(false, false); /* DANGER */
    res_leak_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif
