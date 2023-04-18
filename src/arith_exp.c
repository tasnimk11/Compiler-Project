#include "../include/arith_exp.h"

/***********************/
/***********************/
/*   Macro definition  */
/***********************/
/***********************/

#define  SIZE_INS_TAB 200    // SIZE of the Assembler Instruction Table

#define  SIZE_INS 200         // SIZE of one instruction, in number of characters

/******************/
/******************/
/* Data structure */
/******************/
/******************/

/**
 * @brief Structure of one Operation Element of the Assembler Instruction table
 */

struct op_elem {
    enum opcode_t opcode;   // OPCODE of the operation
    int           ret;      // ADDRESS of the return
    int           operand1; // ADDRESS of the first operand
    int           operand2; // ADDRESS of the second operand
}typedef op_elem;

/******************/
/******************/
/* Global variable*/
/******************/
/******************/

/**
 * @brief Assembler Instruction table
 *
 * @note It is a fixed-size list, nb_ins is used to keep the current number of elements
 */

static op_elem asm_ins_table[SIZE_INS_TAB];

int nb_ins = -1;        // Number of instructions of the Assembler Instruction table

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
 * @return The number of the instruction in the Assembler Instruction table
 */

int add_operation(enum opcode_t opcode, int ret, int operand1, int operand2){
    if (nb_ins == SIZE_INS_TAB){ //limit of the Assembler Instruction table
        printf("Instruction Table Full.\n");
    } else {
        nb_ins++; //increment the number of instructions

        //Add Instruction
        asm_ins_table[nb_ins].opcode = opcode;
        asm_ins_table[nb_ins].ret = ret;
        asm_ins_table[nb_ins].operand1 = operand1;
        asm_ins_table[nb_ins].operand2 = operand2;

    }
    return nb_ins;
}

/**
 * @brief Gets the assembler instruction from the operation element
 *
 * This function is used to translate operations to printable strings
 *
 * @param op_elem The operation to translate
 * @return The corresponding string
 */

char * get_asm_str(op_elem op){
    char * str =malloc(SIZE_INS);
    switch (op.opcode) {
        case (AND):
            sprintf(str,"AND %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (OR):
            sprintf(str,"OR %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (ADD):
            sprintf(str,"ADD %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (SUB):
            sprintf(str,"SUB %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (MUL):
            sprintf(str,"MUL %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (DIV):
            sprintf(str,"DIV %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (LT):
            sprintf(str,"LT %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (LE):
            sprintf(str,"LE %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (GT):
            sprintf(str,"GT %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (GE):
            sprintf(str,"GE %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (EQ):
            sprintf(str,"EQ %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (NE):
            sprintf(str,"NE %4d %4d %4d\n", op.ret, op.operand1, op.operand2);
            break;
        case (NO):
            sprintf(str,"NOT %4d %4d \n", op.ret, op.operand1);
            break;
        case (MOV):
            sprintf(str,"MOV %4d %4d \n", op.ret, op.operand1);
            break;
        case (JMF):
            sprintf(str,"JMF %4d %4d \n", op.operand1, op.operand2);
            break;
        case (JMP):
            sprintf(str,"JMP %4d \n", op.operand2);
            break;
        default:
            break;

    }
    return str;
}

/**
 * @brief Prints the Assembler Instruction Table
 *
 * This function is used to print a table of instructions
 * (state of the ASM file at that step of parsing)
 *
 * @return Nothing
 */

void print_asm_table(){
    if (nb_ins==0) { //empty asm table
        printf("ASM Table is empty.\n");
    } else {
        for (int i=0; i<nb_ins; i++){
            printf("asm = %s", get_asm_str(asm_ins_table[i]));

        }
    }
}



/**
 * @brief Generates the binary file given the Assembler Instruction table
 *
 * This function is used by the parser to generate the ASM file
 *
 * @return Nothing
 */

void generate_binary(){
    FILE * output = fopen("myASM.txt","w"); //open output file
    for (int i = 0; i <= nb_ins; i++){
        char * line = get_asm_str(asm_ins_table[i]);
        fputs(line, output);
        free(line);
    }
    fclose(output); //close output file
}

/**
 * @brief Patches the Jump instructions by adding the line to jump to
 *
 * This function is used by the parser to give the Jump instructions
 * the line where to jump to after calculating the size of the block jump from.
 *
 * @param asm_line The asm line holding the JMP or JMF that needs patching
 * @param jump_to_line The line in the asm to jump to
 * @return Nothing
 */

void patch(int asm_line,int jump_to_line){
    asm_ins_table[asm_line].operand2 = jump_to_line;
}


/**
 * @brief Gets the current instruction number
 *
 * This function is used by the parser to get the current instruction number
 *
 * @return The instruction number
 */

int get_ins_number(){
    return nb_ins;
}
