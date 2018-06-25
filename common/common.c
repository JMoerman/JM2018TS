#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void assign_pointer(void** dest, void* source1, void* source2, bool condition) {
    if(condition) {
        *dest = source1;
    } else {
        *dest = source2;
    }
}

void* choose_pointer(void* source1, void* source2, bool condition) {
    if(condition) {
        return source1;
    } else {
        return source2;
    }
}

void conditional_free(void* ptr, bool condition, void** set_null) {
    if(condition) {
        free(ptr);
        if(set_null) {
            *set_null = 0;
        }
    }
}

int int_dereference_choice(int* source1, int* source2, bool condition) {
    if(condition) {
        return *source1;
    }
    return *source2;
}

int choose_int(int int1, int int2, bool condition) {
    if(condition) {
        return int1;
    } else {
        return int2;
    }
}

void conditional_close(FILE* file, bool do_close, FILE** set_null) {
    if(do_close) {
        fclose(file);
        if(set_null) {
            *set_null = 0;
        }
    }
}
