#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "access_closed.h"

void access_closed_if_else(bool a, bool b) {
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
        val = ((int) fgetc(file)) * 2;
    } else {
        val = (int) fgetc(file);
        fclose(file);
    }

    if(b) {
        val += 37;
    } else {
        val += (int) fgetc(file);
    }

    if(a) {
        fclose(file);
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    access_closed_if_else(true, true);
    access_closed_if_else(true, false);
    access_closed_if_else(false, true);
#else
    access_closed_if_else(true, true); /* OK */
    access_closed_if_else(false, false); /* DANGER */
    access_closed_if_else(false, true); /* OK */
#endif

    return 1;
}
#endif
