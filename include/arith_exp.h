#ifndef ARITH_EXP_H
#define ARITH_EXP_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Define Structures needed for Bison
 *
 */

/*
 * Enum types for operations
 */

enum opcode_t {
    AND,
    OR,
    ADD,
    SUB,
    MUL,
    DIV,
    LT,
    LE,
    GT,
    GE,
    EQ,
    NE,
    NO,
    MOV
};

void add_operation(enum opcode_t operand, int ret, int operand1, int operand2);



#endif
