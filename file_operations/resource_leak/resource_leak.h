#include <stdbool.h>
#include <stdio.h>

typedef struct _ResLeakRefCont FileCont;

struct _ResLeakRefCont {
    FILE* file;
    unsigned int refc;
};

void res_leak_cont_init(FileCont* cont);
FileCont* res_leak_cont_new();
void res_leak_cont_ref(FileCont* cont);
void res_leak_cont_unref(FileCont* cont);
FILE* res_leak_cont_get_file(FileCont* cont);
void res_leak_cont_set_file(FileCont* cont, FILE* file);

void res_leak_for(int x);
void res_leak_for_complex(int x);
void res_leak_while_continue(int x);
void res_leak_do_while_continue(int x);
void res_leak_for_array(int x);
void res_leak_for_pointer(int x);
void res_leak_goto(int x);
void res_leak_if_else(bool a, bool b);
void res_leak_if_else_multi(bool a, bool b);
void res_leak_if_else_int1(int x, int y);
void res_leak_if_else_int2(int x, int y);
void res_leak_pass_by_reference(bool a, bool b);
int res_leak_switch(int x, int y);
int res_leak_rec_multi(int x, int i, FILE** file_ptr, bool do_close);
int res_leak_rec(int x, int i, FILE** file_ptr, bool do_close);
int res_leak_pseudo_rec1(int x, int y, int i, char* file_name);
int res_leak_pseudo_rec2(int x, int y, int i, FILE** file_ptr, char* file_name);
void res_leak_struct(int x, int y);
void res_leak_function_pointer(bool a, bool b, int (*f)(FILE** dest, bool close_file));
void res_leak_cross_file(bool a, bool b);
