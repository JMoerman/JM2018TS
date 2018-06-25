#include "refer_free.h"
#include <stdlib.h>

int refer_free_switch(int x, int y) {
    int* data;
    int val;

#ifdef CATCH_BAD_PARAM
    if((x == 10 || x == 5) && x > y) {
        return -1;
    }
#endif
    data = malloc(5*sizeof(int));

    if(!data) {
        return -1;
    }

    *data = -1;

    if(x > y) {
        free(data);
    }

    switch (x) {
        case 5: {
            val = *data; /* DANGER: x >= y */
            break;
        }
        case 7: {
            val  = 289;
            break;
        }
        case 10: {
            val = *data + 36; /* DANGER: x >= y */
            break;
        }
        case 12: {
            val  = 49807;
            break;
        }
        default: {
            val  = 7987;
            break;
        }
    }

    if(x <= y) {
        free(data);
    }

    return val;
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    refer_free_switch(5, 11);
    refer_free_switch(10, 11);
    refer_free_switch(11, 10);
    refer_free_switch(7, 5);
#else
    refer_free_switch(5, 10); /* OK */
    refer_free_switch(10, 9); /* DANGER */
    refer_free_switch(11, 10); /* OK */
    refer_free_switch(7, 5); /* OK */
#endif

    return 1;
}
#endif
