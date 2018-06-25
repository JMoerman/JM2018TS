#include <stdbool.h>

typedef struct _DivideCont DivideCont;

struct _DivideCont {
    int* possibly_uninit;
    int uninit_val;
    int init_val;
    unsigned int counter;
};

void uninit_val_cont_init(DivideCont* cont);
DivideCont* uninit_val_cont_new();
void uninit_val_cont_incr(DivideCont* cont);
void uninit_val_cont_decr(DivideCont* cont);
int uninit_val_cont_get_value(DivideCont* cont);
void uninit_val_cont_set_value(DivideCont* cont, int value);

void uninit_val_for(int x);
void uninit_val_for_complex(int x);
void uninit_val_while_continue(int x);
void uninit_val_do_while_continue(int x);
void uninit_val_for_array(int x);
void uninit_val_for_pointer(int x);
void uninit_val_goto(int x);
void uninit_val_if_else(bool a, bool b);
void uninit_val_if_else_multi(bool a, bool b);
void uninit_val_if_else_int1(int x, int y);
void uninit_val_if_else_int2(int x, int y);
void uninit_val_pass_by_reference(bool a, bool b);
int uninit_val_switch(int x, int y);
int uninit_val_rec_multi(int x, int i, int* ptr1, int* ptr2);
int uninit_val_rec(int x, int i, int* ptr1, int* ptr2);
int uninit_val_pseudo_rec1(int x, int y, int i, int* ptr1, int* ptr2);
int uninit_val_pseudo_rec2(int x, int y, int i, int* ptr1, int* ptr2);
void uninit_val_struct(int x, int y);
void uninit_val_function_pointer(bool a, bool b, void (*f)(int**, int*, int*, bool));
void uninit_val_cross_file(bool a, bool b);
