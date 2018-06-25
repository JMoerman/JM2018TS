#include <stdio.h>
#include <stdlib.h>
#include "resource_leak.h"

void res_leak_goto(int x) {
    FILE* file = 0;
    int val = 0;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x > 0) {
        return;
    }
#endif

GOTO_LABEL:
    if(i <= x) {
        file = fopen("file.txt","r");

        if(!file) {
            return;
        }

        val += ((int) fgetc(file));
    } else {
        printf("%i\n", val);
    }

    if(i == 0) {
        i++;
        if(file) fclose(file);
        goto GOTO_LABEL;
    }
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_goto(0);
#else
    res_leak_goto(1);
#endif

    return 1;
}
#endif
