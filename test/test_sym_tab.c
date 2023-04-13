#include "sym_tab.h"
#include <stdio.h>

int test_sym() {
    //print_sym_tab empty tab
    printf("\n-------TEST EMPTY TABLE--------\n");
    print_sym_tab();


   
    printf("\n-------TEST PUSH --------------\n");

    push("e1", "int", 0); // add elem
    print_sym_tab(); // print_sym_tab tab

    push("e2", "int", 0); // add elem
    print_sym_tab(); // print_sym_tab tab

    push("e3", "int", 0); // add elem
    print_sym_tab(); // print_sym_tab tab



    printf("\n-------TEST GET OFFSET --------\n");

    printf("    Offset e1 : %d\n", get_offset("e1"));
    printf("    Offset e2 : %d\n", get_offset("e2"));
    printf("    Offset e3 : %d\n", get_offset("e3"));


    printf("\n-------TEST POP  --------------\n");

    pop();
    print_sym_tab(); // print_sym_tab tab
    pop();
    print_sym_tab(); // print_sym_tab ta
    pop();
    print_sym_tab(); // print_sym_tab ta

    
   
}