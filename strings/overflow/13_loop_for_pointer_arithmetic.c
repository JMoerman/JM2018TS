#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_overflow.h"

static void initialize_to_string(char* arr[], char* string, int length) {
    int i;

    for(i = 0; i < length; i++) {
        arr[i] = string;
    }
}

void string_overflow_for_pointer(int x) {
    char* string_arr[10];
    char** ptr;
    char long_string[22] = "this is a long string";
    char short_string[13] = "short string";
    int val = 0, i;

    if(x < 0 || x > 10) {
        return;
    }

#ifdef CATCH_BAD_PARAM
    if(x != 10) {
        return;
    }
#endif

    initialize_to_string(string_arr, short_string, 10);
    initialize_to_string(string_arr, long_string, x);

    ptr = string_arr;

    for(i = 0; i < 10; i++, ptr++) {
        (*string_arr)[13] = (char) i;
    }

    printf("%s\n", *ptr);
}

#ifndef NO_MAIN
int main() {
#ifdef NO_BUG
    string_overflow_for_pointer(10);
#else
    string_overflow_for_pointer(9);
#endif

    return 1;
}
#endif
