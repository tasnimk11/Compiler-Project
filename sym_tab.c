#include "sym_tab.h"

int depth = -1; // Depth of the Symbols table

static elem_tab pile_st[SIZE]; // Symbols Table : Pile -> Fixed-size list

/**
 *
 * PUSH function
 *
 */

void push(char * name, char * typ, int init, int offset, int scope){
    depth++; // increment depth
    elem_tab elem = {name, typ, init, offset, scope};
    pile_st[depth] = elem; //add element 
    //TODO : push second time => issue !
    //TODO : scope !?
    //TODO : offset ?

}

/**
 *
 * POP function
 *
 */
void pop(){
    if (depth>-1){
        depth--; // decrement depth
    } else {
        
    }
}


/**
 *
 * PRINT Pile function
 *
 */

void print(){
    if (depth==-1) { //empty pile_st
        printf("Symbols Table is empty.\n");
    } else {
        for (int i=0; i<=depth; i++){
            printf("%s | %s | %d | %d | %d .\n",
                   pile_st[i].name,
                   pile_st[i].type,
                   pile_st[i].init,
                   pile_st[i].offset,
                   pile_st[i].scope
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
    for (int i = 0; i <= depth; i++){
        if (pile_st[i].name == name)
        {
            return pile_st[i].offset;
        }
    }
    return -1; 
}
