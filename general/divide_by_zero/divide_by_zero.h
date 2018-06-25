#include <stdbool.h>

typedef struct _DivideCont DivideCont;

struct _DivideCont {
    int divisor;
    unsigned int counter;
};

DivideCont* divide_zero_cont_new();
void divide_zero_cont_incr(DivideCont* cont);
void divide_zero_cont_decr(DivideCont* cont);
int divide_zero_cont_get_divisor(DivideCont* cont);
void divide_zero_cont_set_divisor(DivideCont* cont, int divisor);

void divide_zero_for(int x);
void divide_zero_for_complex(int x);
void divide_zero_while_continue(int x);
void divide_zero_do_while_continue(int x);
void divide_zero_for_array(int x);
void divide_zero_for_pointer(int x);
void divide_zero_goto(int x);
void divide_zero_if_else(bool a, bool b);
void divide_zero_if_else_multi(bool a, bool b);
void divide_zero_if_else_int1(int x, int y);
void divide_zero_if_else_int2(int x, int y);
void divide_zero_pass_by_reference(bool a, bool b);
int divide_zero_switch(int x, int y);
int divide_zero_rec_multi(int x, int i, int div1, int div2);
int divide_zero_rec(int x, int i, int div1, int div2);
int divide_zero_pseudo_rec1(int x, int y, int i, int div1, int div2);
int divide_zero_pseudo_rec2(int x, int y, int i, int div1, int div2);
void divide_zero_struct(int x, int y);
void divide_zero_function_pointer(bool a, bool b, void (*f)(int*, int, int, bool));
void divide_zero_cross_file(bool a, bool b);
