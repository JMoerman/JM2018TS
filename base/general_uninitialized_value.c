#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;

#ifdef NO_BUG
    x = 5;
#endif

    printf("%i\n", x + 1);

    return 1;
}
