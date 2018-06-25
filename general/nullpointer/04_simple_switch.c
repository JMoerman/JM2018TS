#include "nullpointer.h"

int nullpointer_switch(int x, int y) {
    int arr[3] = {1, 2, 3};
    int* ptr = 0;
    int val;

#ifdef CATCH_BAD_PARAM
    if((x == 10 || x == 5) && x >= y) {
        return -1;
    }
#endif

    if(x < y) {
        ptr = arr;
    }

    switch (x) {
        case 5: {
            val = *(ptr+2); /* DANGER: x >= y */
            break;
        }
        case 7: {
            val = arr[0] + 5;
            break;
        }
        case 10: {
            val = *ptr; /* DANGER: x >= y */
            break;
        }
        case 12: {
            val = arr[2] + 5;
            break;
        }
        default: {
            val = arr[1];
            break;
        }
    };

    return val;
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    nullpointer_switch(5, 11);
    nullpointer_switch(10, 11);
    nullpointer_switch(11, 10);
    nullpointer_switch(7, 5);
#else
    nullpointer_switch(5, 10); /* OK */
    nullpointer_switch(10, 10); /* DANGER */
    nullpointer_switch(11, 10); /* OK */
    nullpointer_switch(7, 5); /* OK */
#endif

    return 1;
}
#endif
