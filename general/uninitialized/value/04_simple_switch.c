#include "uninitialized_value.h"

int uninit_val_switch(int x, int y) {
    int possibly_uninit;
    int val;

#ifdef CATCH_BAD_PARAM
    if((x == 10 || x == 5) && x >= y) {
        return -1;
    }
#endif

    if(x < y) {
        possibly_uninit = 1;
    }

    switch (x) {
        case 5: {
            val = 37 * possibly_uninit; /* DANGER: x >= y */
            break;
        }
        case 7: {
            val = -37 * 2;
            break;
        }
        case 10: {
            val = 73 * possibly_uninit; /* DANGER: x >= y */
            break;
        }
        case 12: {
            val = 73 * 5;
            break;
        }
        default: {
            val = 100 * 8;
            break;
        }
    };

    return val;
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    uninit_val_switch(5, 11);
    uninit_val_switch(10, 11);
    uninit_val_switch(11, 11);
    uninit_val_switch(7, 5);
#else
    uninit_val_switch(5, 10); /* OK */
    uninit_val_switch(10, 10); /* DANGER */
    uninit_val_switch(11, 10); /* OK */
    uninit_val_switch(7, 5); /* OK */
#endif

    return 1;
}
#endif
