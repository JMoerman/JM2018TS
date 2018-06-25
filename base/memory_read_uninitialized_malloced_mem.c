#include <stdio.h>
#include <stdlib.h>

int main() {
    int* data;

    data = malloc(sizeof(int));


    if(!data) {
        return -1;
    }

#ifdef NO_BUG
    *data = 37;
#endif

    printf("%i\n", *data);

    free(data);

    return 1;
}
