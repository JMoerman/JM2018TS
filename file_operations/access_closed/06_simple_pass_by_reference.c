#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "access_closed.h"

static int assign_possibly_closed(FILE** dest, bool close_file) {
    int val;
    FILE* file = fopen("file.txt","r");
    *dest = file;
    if(!file) {
        return -1;
    }
    val = (int) fgetc(file);
    if(close_file) {
        fclose(file);
    }
    return val;
}

void access_closed_pass_by_reference(bool a, bool b) {
    FILE* file;
    int val;

#ifdef CATCH_BAD_PARAM
    if(!a & !b) {
        return;
    }
#endif

    val = assign_possibly_closed(&file, !a);

    if(!b && file) {
        val += (int) fgetc(file);
    } else {
        val += 687;
    }

    if(a && file) {
        fclose(file);
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    access_closed_pass_by_reference(true, true);
    access_closed_pass_by_reference(true, false);
    access_closed_pass_by_reference(false, true);
#else
    access_closed_pass_by_reference(true, true); /* OK */
    access_closed_pass_by_reference(false, false); /* DANGER */
    access_closed_pass_by_reference(false, true); /* OK */
#endif

    return 1;
}
#endif
