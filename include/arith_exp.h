#ifndef ARITH_EXP_H
#define ARITH_EXP_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/******************/
/******************/
/* Data structure */
/******************/
/******************/

/**
 * @brief Enumeration of OPCODE types
 *
 * This enumeration defines the types of opcodes will be used in the Assembly Machine code program
 */
enum opcode_t {
    AND, //AND opcode
    OR,  // OR opcode
    ADD, // ADD (addition) opcode
    SUB, // SUB (subtract) opcode
    MUL, // MUL (multiply) opcode
    DIV, // DIV (divide) opcode
    LT,  // LT (less than) opcode
    LE,  // LE (less than or equal to) opcode
    GT,  // GT (greater than) opcode
    GE,  // GE (greater than or equal to) opcode
    EQ,  // EQ (equal to) opcode
    NE,  // NE (not equal to) opcode
    NO,  // NO (not) opcode
    MOV  // MOV (move, copy, assign) opcode
};


/***********************/
/***********************/
/* Function definition */
/***********************/
/***********************/


/**
 * @brief Adds the operation to the Assembler Instruction table
 *
 * This function is used by the parser to add the operations to an ASM table
 *
 * @param opcode The corresponding opcode to the ASM definition
 * @param ret The address where to return the result of the operation
 * @param operand1 The first operand of the operation
 * @param operand2 The second operand of the operation
 * @return Nothing
 */

void add_operation(enum opcode_t opcode, int ret, int operand1, int operand2);


/**
 * @brief Prints the Assembler Instruction Table
 *
 * This function is used to print a table of instructions
 * (state of the ASM file at that step of parsing)
 *
 * @return Nothing
 */

void print_asm_table();

/**
 * @brief Generates the binary file given the Assembler Instruction table
 *
 * This function is used by the parser to generate the ASM file
 *
 * @return Nothing
 */

void generate_binary();

#endif
