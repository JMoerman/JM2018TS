#include "resource_leak.h"
#include <stdbool.h>
#include <stdlib.h>

int res_leak_switch(int x, int y) {
    FILE* file;
    bool closed = false;
    int val = 0;

#ifdef CATCH_BAD_PARAM
    if((x == 10 || x == 5) && x > y) {
        return -1;
    }
#endif
    file = fopen("file.txt","r");

    if(!file) {
        return -1;
    }

    if(x <= y) {
        fclose(file);
        closed = true;
    }

    switch (x) {
        case 5: {
            if(!closed) val = ((int) fgetc(file));
            closed = true; /* DANGER: x >= y */
            break;
        }
        case 7: {
            if(!closed) {
                val  = ((int) fgetc(file)) + 289;
                fclose(file);
                closed = true;
            }
            break;
        }
        case 10: {
            if(!closed) {
                val = ((int) fgetc(file)) + 36;
                closed = true; /* DANGER: x >= y */
            }
            break;
        }
        case 12: {
            if(!closed) {
                val  = ((int) fgetc(file)) + 49807;
                fclose(file);
            }
            closed = true;
            break;
        }
        default: {
            val  = 7987;
            break;
        }
    }

    if(!closed) {
        fclose(file);
    }

    return val;
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    res_leak_switch(5, 11);
    res_leak_switch(10, 11);
    res_leak_switch(11, 10);
    res_leak_switch(7, 5);
#else
    res_leak_switch(5, 10); /* OK */
    res_leak_switch(10, 9); /* DANGER */
    res_leak_switch(11, 10); /* OK */
    res_leak_switch(7, 5); /* OK */
#endif

    return 1;
}
#endif
