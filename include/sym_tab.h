#ifndef SYM_TAB
#define SYM_TAB

#include <stdlib.h>
#include <string.h>
#include <stdio.h>




int push(char * name, char * type, int isInit);

int push_param(char * name, char * type, int isInit);

void pop();

void print_sym_tab();

int get_addr(char *elem_name);

void increment_scope();

void decrement_scope();


#endif
