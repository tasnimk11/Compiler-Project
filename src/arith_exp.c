#include "../include/arith_exp.h"

/**
 * One element of the symbols table.
 */


void add_operation(enum opcode_t opecode, int ret, int operand1, int operand2){

    switch(opecode){
        case(AND):
            printf("AND %d %d %d\n",ret, operand1, operand2);
            break;
        case(OR):
            printf("OR %d %d %d\n",ret, operand1, operand2);
            break;
        case(ADD):
            printf("ADD %d %d %d\n",ret, operand1, operand2);
            break;
        case(SUB):
            printf("SUB %d %d %d\n",ret, operand1, operand2);
            break;
        case(MUL):
            printf("MUL %3d %3d %3d\n",ret, operand1, operand2);
            break;
        case(DIV):
            printf("DIV %4d %4d %4d\n",ret, operand1, operand2);
            break;
        case(LT):
            printf("LT %4d %4d %4d\n",ret, operand1, operand2);
            break;
        case(LE):
            printf("LE %4d %4d %4d\n",ret, operand1, operand2);
            break;
        case(GT):
            printf("GT %4d %4d %4d\n",ret, operand1, operand2);
            break;
        case(GE):
            printf("GE %4d %4d %4d\n",ret, operand1, operand2);
            break;
        case(EQ):
            printf("EQ %4d %4d %4d\n",ret, operand1, operand2);
            break;
        case(NE):
            printf("NE %4d %4d %4d\n",ret, operand1, operand2);
            break;
        case(NO):
            printf("NO %4d %4d \n",ret, operand1);
            break;
        case(MOV):
            printf("MOV %4d %4d \n",ret, operand1);
            break;
        default :
            printf("default");
            break;
    }

}


