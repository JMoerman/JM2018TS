#include <stdio.h>
#include <stdlib.h>
#include "access_closed.h"

void access_closed_for_complex(int x) {
    FILE* file;
    int val = 0;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif

    file = fopen("file1.txt","r");

    if(!file) {
        return;
    }

    val = (int) fgetc(file);

    fclose(file);

    for(;;) {
        if(i > x) {
            val += (int) fgetc(file);
        } else {
            val += 24;
        }
        if(i == 10) {
            file = fopen("file2.txt","r");
            if(!file) {
                return;
            }
        }
        i++;
        if(i >= 20) {
            break;
        }
    }

    fclose(file);

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    access_closed_for_complex(10);
#else
    access_closed_for_complex(9);
#endif

    return 1;
}
#endif
