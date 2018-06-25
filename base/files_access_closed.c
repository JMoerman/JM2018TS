#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file;

    file = fopen("file.txt","r");

    if(!file) {
        return;
    }

#ifdef NO_BUG
    printf("%i\n", (int) fgetc(file));
    fclose(file);
#else
    fclose(file);
    printf("%i\n", (int) fgetc(file));
#endif

    return 1;
}
