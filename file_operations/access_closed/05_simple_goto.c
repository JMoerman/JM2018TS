#include <stdio.h>
#include <stdlib.h>
#include "access_closed.h"

void access_closed_goto(int x) {
    FILE* file = 0;
    int val = 0;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x > 0) {
        return;
    }
#endif

    file = fopen("file.txt","r");

    if(!file) {
        return;
    }

GOTO_LABEL:
    if(i <= x) {
        val += ((int) fgetc(file));
    } else {
        printf("%i\n", val);
    }

    if(i == 0) {
        i++;
        fclose(file);
        goto GOTO_LABEL;
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    access_closed_goto(0);
#else
    access_closed_goto(1);
#endif

    return 1;
}
#endif
