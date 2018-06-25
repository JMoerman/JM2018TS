#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "resource_leak.h"

void res_leak_for_array(int x) {
    FILE* file = 0;
    int p[20];
    int val = 0;
    bool do_close = true;
    int i;

#ifdef CATCH_BAD_PARAM
    if(x != 19) {
        return;
    }
#endif

    for(i = 0; i < 20; i++) {
        p[i] = 0;
    }
    p[x] = 1;

    for(i = 0; i < 20; i++) {
        if(p[i] == 1) {
            do_close = false;
        } else {
            if(!file) file = fopen("file.txt","r");

            if(!file) {
                return;
            }

            val += ((int) fgetc(file)) + i;
            if(do_close) {
                fclose(file);
                file = 0;
            }
        }
    }

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_for_array(19);
#else
    res_leak_for_array(10);
#endif

    return 1;
}
#endif
