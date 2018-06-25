#include "double_free.h"
#include <stdlib.h>

void double_free_switch(int x, int y) {
    int* data;

#ifdef CATCH_BAD_PARAM
    if((x == 10 || x == 5) && x > y) {
        return;
    }
#endif
    data = malloc(5*sizeof(int));

    if(!data) {
        return;
    }

    if(x > y) {
        free(data);
    }

    switch (x) {
        case 5: {
            free(data); /* DANGER: x >= y */
            break;
        }
        case 7: {
            if(x <= y) free(data);
            break;
        }
        case 10: {
            free(data); /* DANGER: x >= y */
            break;
        }
        case 12: {
            if(x <= y) free(data);
            break;
        }
        default: {
            if(x <= y) free(data);
            break;
        }
    };
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    double_free_switch(5, 11);
    double_free_switch(10, 11);
    double_free_switch(11, 10);
    double_free_switch(7, 5);
#else
    double_free_switch(5, 10); /* OK */
    double_free_switch(10, 9); /* DANGER */
    double_free_switch(11, 10); /* OK */
    double_free_switch(7, 5); /* OK */
#endif

    return 1;
}
#endif
