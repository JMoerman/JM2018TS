#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "access_closed.h"

void access_closed_for_array(int x) {
    FILE* file = 0;
    int p[20];
    int val = 0;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x != 19) {
        return;
    }
#endif

    file = fopen("file.txt","r");

    if(!file) {
        return;
    }

    for(i = 0; i < 20; i++) {
        p[i] = 0;
    }
    p[x] = 1;

    for(i = 0; i < 20; i++) {
        if(p[i] == 1) {
            fclose(file);
        } else {
            val += ((int) fgetc(file)) + i;
        }
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    access_closed_for_array(19);
#else
    access_closed_for_array(10);
#endif

    return 1;
}
#endif
