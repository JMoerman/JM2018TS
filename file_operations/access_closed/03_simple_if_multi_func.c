#include "access_closed.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void conditional_close(FILE** ptr, bool condition) {
    if(condition) {
        fclose(*ptr);
    }
}

static int conditional_fgetc(FILE** ptr, int def, bool condition) {
    if(condition) {
        return fgetc(*ptr);
    }
    return def;
}

void access_closed_if_else_multi(bool a, bool b) {
    int val;
    FILE* file;
    FILE** file_ptr = &file;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif
    file = fopen("file.txt","r");

    if(!file) {
        return;
    }

    conditional_close(file_ptr, !a);
    val = conditional_fgetc(file_ptr, 897, !b);
    conditional_close(file_ptr, a);

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    access_closed_if_else_multi(true, true);
    access_closed_if_else_multi(true, false);
    access_closed_if_else_multi(false, true);
#else
    access_closed_if_else_multi(true, true); /* OK */
    access_closed_if_else_multi(false, false); /* DANGER */
    access_closed_if_else_multi(false, true); /* OK */
#endif
    return 1;
}
#endif
