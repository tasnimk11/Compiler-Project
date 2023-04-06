#include "sym_tab.h"
#include <stdio.h>

int main() {
    //print empty tab
    printf("\n-------TEST EMPTY TABLE--------\n");
    print();


   
    printf("\n-------TEST PUSH --------------\n");

    push("e1", "int", 0, 100, 100); // add elem
    print(); // print tab

    push("e2", "int", 0, 200, 200); // add elem
    print(); // print tab

    push("e3", "int", 0, 300, 300); // add elem
    print(); // print tab



    printf("\n-------TEST GET OFFSET --------\n");

    printf("    Offset e1 : %d\n", get_offset("e1"));
    printf("    Offset e2 : %d\n", get_offset("e2"));
    printf("    Offset e3 : %d\n", get_offset("e3"));


    printf("\n-------TEST POP  --------------\n");

    pop();
    print(); // print tab
    pop();
    print(); // print ta
    pop();
    print(); // print ta

    
   
}