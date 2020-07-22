#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file;

    file = fopen("file.txt","r");

    if(!file) {
        return 0;
    }

    printf("%i\n", (int) fgetc(file));

#ifdef NO_BUG
    fclose(file);
#else
    fclose(file);
    fclose(file);
#endif

    return 1;
}
