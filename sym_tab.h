#define SYM_TAB

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 50

/**
 * Structures declarations
 */



/**
 * One element of the symbols table.
 *
 */
struct elem_tab {
    char *name; // name of the elemet
    char *type; // type of the element
    int  init;     // true if the element has already been initialized
    int  offset;   // offset of the element compared to the bs of the execution pile
    int  scope;    // scope of the element (compared to the other functions)
} typedef elem_tab;





void push(char * name, char * type, int init, int offset, int scope);

void pop();

void print();

int get_offset(char *elem_name);
