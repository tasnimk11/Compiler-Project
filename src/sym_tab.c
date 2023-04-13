#include "sym_tab.h"

#define      SIZE 65536 // in bytes

#define  INT_SIZE 1     // in bytes
#define   ID_SIZE 16    // in bytes
#define TYPE_SIZE 3     // in bytes

/**
 * Structures declarations
 */

/**
 * One element of the symbols table.
 */
struct elem
{
    char name[ID_SIZE]; // name of the elemet
    char type[TYPE_SIZE];  // type of the element
    int  isInit;      // true if the element has already been initialized
    int  offset;    // offset of the element compared to the bs of the execution stack
    int  scope;     // scope of the element (compared to the other functions)
} typedef elem;


int nb_elem = -1; // nb_elem of the Symbols table
int scope   = -1; // increments with each block
int offset  = 0 ; // Increments according to size of INT (1 BYTE)

static elem stack_st[SIZE]; // Symbols Table : Stack -> Fixed-size list

/**
 *
 * PUSH function
 *
 */

void push(char * name, char * type, int isInit){
    //Verify if element hasn't been added before
    for(int i=0; i<=nb_elem; i++){
        if(strcmp(name, stack_st[i].name) == 0){
            printf("Element already defined.\n");
            exit(-1);
        }
    }

    nb_elem++; // increment nb_elem
    offset += INT_SIZE; // increment offset
    strcpy(stack_st[nb_elem].name, name);
    strcpy(stack_st[nb_elem].type, type);
    stack_st[nb_elem].isInit = isInit;
    stack_st[nb_elem].offset = offset;
    stack_st[nb_elem].scope = scope;
}


/**
 *
 * PUSH_PARAM function : considers the fuction param declaration
 *
 */

void push_param(char * name, char * type, int isInit){
    //Verify if element hasn't been added before
    for(int i=0; i<=nb_elem; i++){
        if(strcmp(name, stack_st[i].name) == 0){
            printf("Element already defined.\n");
            exit(-1);
        }
    }

    nb_elem++; // increment nb_elem
    offset += INT_SIZE; // increment offset
    strcpy(stack_st[nb_elem].name, name);
    strcpy(stack_st[nb_elem].type, type);
    stack_st[nb_elem].isInit = isInit;
    stack_st[nb_elem].offset = offset;
    stack_st[nb_elem].scope = scope+1;
}


/**
 *
 * POP function
 *
 */
void pop(){
    if (nb_elem>-1){
        nb_elem--; // decrement nb_elem
        offset-=INT_SIZE;
    } else {
        printf("Symbols Table is empty.\n");
    }
}


/**
 *
 * PRINT stack function
 *
 */

void print_sym_tab(){
    if (nb_elem==-1) { //empty stack_st
        printf("Symbols Table is empty.\n");
    } else {
        for (int i=0; i<=nb_elem; i++){
            printf("%8s | %5s | %1d | %3d | %3d .\n",
                   stack_st[i].name,
                   stack_st[i].type,
                   stack_st[i].isInit,
                   stack_st[i].offset,
                   stack_st[i].scope
                   );
        }
    }
}


/**
 * 
 * GET_OFFSET function
 *      return offset of the elements, -1 if elemnt not in table
 */

int get_offset(char * name){
    for (int i = 0; i <= nb_elem; i++){
        if (stack_st[i].name == name) {
            return stack_st[i].offset;
        }
    }
    return -1; 
}

/**
 *
 * INCREMENT_SCOPE function
 *
 */
void increment_scope(){
    scope++;
}


/**
 *
 * DECREMENT_SCOPE function
 *
 */
void decrement_scope(){

    //pop all those of current scope
    int tmp = nb_elem;
    for (int i = 0; i <= tmp; i++){
        if (stack_st[i].scope == scope) {
            pop();
        }
    }
    //decrement scope
    scope--;
}
