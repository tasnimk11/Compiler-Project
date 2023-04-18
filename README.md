# Compiler-Project

## Assembler Spec

We consider @X the address where the value of X is stored.

| ASM Instruction   | Description                                                          |
|-------------------|----------------------------------------------------------------------|
| `AND @Ret @A @B`  | store A and B in Ret                                                 |
| `OR  @Ret @A @B`  | store A or B in Ret                                                  |
| `ADD @Ret @A @B`  | add A to B and store the result in Ret                               |
| `SUB @Ret @A @B`  | sub B to A and store the result in Ret                               |
| `MUL @Ret @A @B`  | multiply A to B and store the result in Ret                          |
| `DIV @Ret @A @B`  | divide A on B and store the result in Ret                            |
| `LT  @Ret @A @B`  | if A is less than B then store 1 in Ret, else 0 in Ret               |
| `LE  @Ret @A @B`  | if A is less than or equal to B then store 1 in Ret, else 0 in Ret   |
| `GT  @Ret @A @B`  | if A is greater than B then store 1 in Ret, else 0 in Ret            |
| `GE  @Ret @A @B`  | if A is greater than or equal to B then store 1 in Ret, else 0 in Ret |
| `EQ  @Ret @A @B`  | if A is equal to B then store 1 in Ret, else 0 in Ret                |
| `NE  @Ret @A @B`  | if A is not equal to B then store 1 in Ret, else 0 in Ret            |
| `NO  @Ret @A`     | store not A in Ret                                                   |
| `MOV @Ret @A`     | move, copy, assign A to Ret                                          |
| `JMF @Cond @Line` | jump to Line if Cond is False                                        |
| `JMP @Line`       | jump to Line                                                         |

