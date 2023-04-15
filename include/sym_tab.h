#ifndef SYM_TAB
#define SYM_TAB

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int push(char * name, char * type, int isInit);


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

int push_param(char * name, char * type, int isInit);


/**
 * @brief Pops elements of the Symbols Table.
 *
 * @return Nothing
 */

void pop();

/**
 * @brief Prints the Symbols Table
 *
 * This function is used to print the symbols table
 *
 * @return Nothing
 */

void print_sym_tab();

/**
 * @brief Get the address of the element from the Symbols Table
 *
 * This function is used to print the symbols table
 *
 * @param elem_name This is the name of the element (variable, TMP, parameter) we are looking for
 * @return Address of the element
 */

int get_addr(char *elem_name);

/**
 * @brief Increments the scope of the elements of the Symbols Table
 *
 * This function is used by the parser to increment the scope whenever it enters a new block.
 *
 * @return Nothing
 */

void increment_scope();

/**
 * @brief Decrements the scope of the elements of the Symbols Table
 *
 * This function is used by the parser to decrement the scope whenever it quits a block.
 *
 * @return Nothing
 */

void decrement_scope();


#endif
