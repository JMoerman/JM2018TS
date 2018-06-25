#include <stdbool.h>

typedef struct _IntCont IntCont;

struct _IntCont {
    int int_value;
    unsigned int counter;
};

void integer_overflow_cont_init(IntCont* cont);
IntCont* integer_overflow_cont_new();
void integer_overflow_cont_incr(IntCont* cont);
void integer_overflow_cont_decr(IntCont* cont);
int integer_overflow_cont_get_int(IntCont* cont);
void integer_overflow_cont_set_int(IntCont* cont, int int_value);

void integer_overflow_for(int x);
void integer_overflow_for_complex(int x);
void integer_overflow_while_continue(int x);
void integer_overflow_do_while_continue(int x);
void integer_overflow_for_array(int x);
void integer_overflow_for_pointer(int x);
void integer_overflow_goto(int x);
void integer_overflow_if_else(bool a, bool b);
void integer_overflow_if_else_multi(bool a, bool b);
void integer_overflow_if_else_int1(int x, int y);
void integer_overflow_if_else_int2(int x, int y);
void integer_overflow_pass_by_reference(bool a, bool b);
void integer_overflow_switch(int x, int y);
void integer_overflow_rec_multi(int x, int i, int val);
void integer_overflow_rec(int x, int i, int val);
void integer_overflow_pseudo_rec1(int x, int y, int i, int val);
void integer_overflow_pseudo_rec2(int x, int y, int i, int val);
void integer_overflow_struct(int x, int y);
void integer_overflow_function_pointer(bool a, bool b, void (*f)(int*, int, int, bool));
void integer_overflow_cross_file(bool a, bool b);
