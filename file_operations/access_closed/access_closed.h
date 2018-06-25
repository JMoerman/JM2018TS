#include <stdbool.h>
#include <stdio.h>

typedef struct _ResLeakRefCont FileCont;

struct _ResLeakRefCont {
    FILE* file;
    unsigned int refc;
};

void access_closed_cont_init(FileCont* cont);
FileCont* access_closed_cont_new();
void access_closed_cont_ref(FileCont* cont);
void access_closed_cont_unref(FileCont* cont);
FILE* access_closed_cont_get_file(FileCont* cont);
void access_closed_cont_set_file(FileCont* cont, FILE* file);

void access_closed_for(int x);
void access_closed_for_complex(int x);
void access_closed_while_continue(int x);
void access_closed_do_while_continue(int x);
void access_closed_for_array(int x);
void access_closed_for_pointer(int x);
void access_closed_goto(int x);
void access_closed_if_else(bool a, bool b);
void access_closed_if_else_multi(bool a, bool b);
void access_closed_if_else_int1(int x, int y);
void access_closed_if_else_int2(int x, int y);
void access_closed_pass_by_reference(bool a, bool b);
int access_closed_switch(int x, int y);
int access_closed_rec_multi(int x, int i, FILE** file_pt);
int access_closed_rec(int x, int i, FILE** file_ptr);
int access_closed_pseudo_rec1(int x, int y, int i, FILE** file_ptr);
int access_closed_pseudo_rec2(int x, int y, int i, FILE** file_ptr);
void access_closed_struct(int x, int y);
void access_closed_function_pointer(bool a, bool b, int (*f)(FILE** dest, bool close_file));
void access_closed_cross_file(bool a, bool b);
