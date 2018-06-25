#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;

#ifdef NO_BUG
    x = 1;
#else
    x = 0;
#endif

    printf("%i\n", 5 / x);

    return 1;
}
