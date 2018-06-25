#include <stdio.h>
#include <stdlib.h>
#include "refer_free.h"

void refer_free_for_complex(int x) {
    int* data;
    int val = 0;
    int i = 0;

#ifdef CATCH_BAD_PARAM
    if(x < 10) {
        return;
    }
#endif
    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    free(data);

    for(;;) {
        if(i > x) {
            val += *data; /* Dangerous if x < 10 */
        } else {
            val += 37;
        }
        if(i == 10) {
            data = malloc(5*sizeof(int));
            if(!data) {
                return;
            }
            *data = 9;
        }
        i++;
        if(i >= 20) {
            break;
        }
    }

    free(data);

    printf("%i\n", val);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    refer_free_for_complex(10);
#else
    refer_free_for_complex(9);
#endif

    return 1;
}
#endif
