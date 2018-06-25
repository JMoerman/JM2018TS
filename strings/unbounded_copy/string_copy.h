#include <stdbool.h>

typedef struct _StringCont StringCont;

struct _StringCont {
    char** selected_string;
    char* normal_string;
    char* small_string;
    unsigned int counter;
};

void string_copy_cont_init(StringCont* cont);
StringCont* string_copy_cont_new();
void string_copy_cont_incr(StringCont* cont);
void string_copy_cont_decr(StringCont* cont);
char* string_copy_cont_get_string(StringCont* cont);
void string_copy_cont_set_string(StringCont* cont, char* string);

void string_copy_for(int x);
void string_copy_for_complex(int x);
void string_copy_while_continue(int x);
void string_copy_do_while_continue(int x);
void string_copy_for_array(int x);
void string_copy_for_pointer(int x);
void string_copy_goto(int x);
void string_copy_if_else(bool a, bool b);
void string_copy_if_else_multi(bool a, bool b);
void string_copy_if_else_int1(int x, int y);
void string_copy_if_else_int2(int x, int y);
void string_copy_pass_by_reference(bool a, bool b);
void string_copy_switch(int x, int y);
void string_copy_rec_multi(int x, int i, char* to_print);
void string_copy_rec(int x, int i, char* to_print);
void string_copy_pseudo_rec1(int x, int y, int i, char* to_print);
void string_copy_pseudo_rec2(int x, int y, int i, char* to_print);
void string_copy_struct(int x, int y);
void string_copy_function_pointer(bool a, bool b, void (*f)(char**, bool));
void string_copy_cross_file(bool a, bool b);
