#include <stdbool.h>
#include <stdio.h>

int int_dereference_choice(int* source1, int* source2, bool condition);
void* choose_pointer(void* source1, void* source2, bool condition);
void conditional_free(void* ptr, bool condition, void** set_null);
int choose_int(int int1, int int2, bool condition);
void conditional_close(FILE* file, bool do_close, FILE** set_null);
void assign_pointer(void** dest, void* source1, void* source2, bool condition);
