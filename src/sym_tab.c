#include "sym_tab.h"

/***********************/
/***********************/
/*   Macro definition  */
/***********************/
/***********************/

#define SIZE_SYM_TAB 65536 // SIZE of the Symbols Table

#define INT_SIZE 1         // SIZE of the INT type

#define ID_SIZE 16         // SIZE of the string withholding the ID of the symbol

#define TYPE_SIZE 3        // SIZE of the string withholding the TYPE of the symbol

/******************/
/******************/
/* Data structure */
/******************/
/******************/

/**
 * @brief Structure of one Operation Element of the Assembler Instruction table
 */
struct s_elem {
    char name[ID_SIZE];    // NAME of the element
    char type[TYPE_SIZE];  // TYPE of the element
    int  isInit;           // 1 if the element has already been initialized, 0 otherwise
    int  offset;           // OFFSET of the element (the Address, for this compiler)
    int  scope;            // SCOPE of the element (compared to the other functions)
} typedef s_elem;


/******************/
/******************/
/* Global variable*/
/******************/
/******************/

/**
 * @brief Symbols Table
 *
 * @note It is a fixed-size Stack, nb_list is used as stack pointer
 */

static s_elem stack_st[SIZE_SYM_TAB]; // Symbols Table : Stack -> Fixed-size list

int nb_elem = -1;                     // number of elements of the Symbols Table

int scope   = -1;                     // the scope of the element in the program

int offset  = 0 ;                     // the offset of the element in the Symbols Table = The address

/***********************/
/***********************/
/* Function definition */
/***********************/
/***********************/

/**
 * @brief Pushes variables declarations to the Symbols Table.
 *
 * @param name The name of the variable
 * @param type The type of the variable (int)
 * @param isInit 1 if it has been initialized, 0 otherwise
 * @return The address of the pushed element
 *
 * @note the name of a temporary variable is set to : TMP
 */

int push(char * name, char * type, int isInit){
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

    return offset; //return address
}


/**
 * @brief Pushes parameters declarations to the Symbols Table.
 *
 * @param name The name of the variable
 * @param type The type of the variable (int)
 * @param isInit 1 if it has been initialized, 0 otherwise
 * @return The address of the pushed element
 *
 * @note it differs for not incrementing the scope, if a parameter is declraed
 */

int push_param(char * name, char * type, int isInit){
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

    return offset; //return address
}


/**
 * @brief Pops elements of the Symbols Table.
 *
 * @return Nothing
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
 * @brief Prints the Symbols Table
 *
 * This function is used to print the symbols table
 *
 * @return Nothing
 */

void print_sym_tab(){
    if (nb_elem==-1) { //empty stack_st
        printf("Symbols Table is empty.\n");
    } else {
        for (int i=0; i<=nb_elem; i++){
            printf("%8s | %4s | %4d | %4d | %4d .\n",
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
 * @brief Get the address of the element from the Symbols Table
 *
 * This function is used to print the symbols table
 *
 * @param elem_name This is the name of the element (variable, TMP, parameter) we are looking for
 * @return Address of the element
 *
 * @note In this compiler, the address is equal to the offset in the table
 */

int get_addr(char * name){
    for (int i = 0; i <= nb_elem; i++){
        if (strcmp(name, stack_st[i].name) == 0) {
            return stack_st[i].offset;
        }
    }

    printf("None Existing Symbol.\n");

    return -1; 
}

/**
 * @brief Increments the scope of the elements of the Symbols Table
 *
 * This function is used by the parser to increment the scope whenever it enters a new block.
 *
 * @return Nothing
 */

void increment_scope(){
    scope++;
}


/**
 * @brief Decrements the scope of the elements of the Symbols Table
 *
 * This function is used by the parser to decrement the scope whenever it quits a block.
 *
 * @return Nothing
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
