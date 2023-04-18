%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "sym_tab.h"
  #include "arith_exp.h"

  int nb_line; //Number of line (used in the ifs)
%}

%code provides {
  int yylex (void);
  void yyerror (const char *);
}

%union{
    int  numD;
    char name[16];
}

%token <numD>  tNB
%token tINT tVOID
%token <name> tID
%token tCOMMA tSEMI 
%token tRETURN tPRINT tWHILE  
%token tNO 

%nonassoc tLPAR tRPAR
%nonassoc tLBRACE tRBRACE

%left tADD tSUB
%left tMUL tDIV
%left tAND
%left tOR
%nonassoc tLT tLE tGT tGE
%nonassoc tEQ tNE

%precedence NOT

%token tIF
%token tELSE

%token tASSIGN

%type<numD> exp


%%

funs : funs fun {
			generate_binary();
		}
     | fun      {
			generate_binary();
		}
     ;

fun : header_int  body_int 
    | header_void body_void
    ;

header_void : tVOID tID tLPAR params tRPAR
;

header_int : tINT tID tLPAR params tRPAR
;

params : tVOID
       | param params1
       | %empty
       ;

params1 : tCOMMA param params1
        | %empty
        ;

param : tINT tID{
			  push_param($2,"int",0);
		 }
	 ;

body_void : tLBRACE {
			increment_scope(); //Block start => increment scope
		    }
            ins
            tRBRACE {
 			decrement_scope(); //Block end => decrement scope
		    }
	    ;

body_int : tLBRACE  {
			increment_scope(); //Block start => increment scope
		    }
	   ins
	   return
	   tRBRACE {
			decrement_scope(); //Block end => decrement scope
		    }
	   ;

return : tRETURN exp tSEMI
	;

ins : in ins 
    | %empty
    ;

in : print tSEMI
   | while 
   | if 
   | declares tSEMI
   | assign tSEMI
   | call tSEMI
   ;

print : tPRINT tLPAR exp tRPAR
	;

while  : tWHILE tLPAR exp tRPAR {
					int nb_ins = add_operation(JMF,-1,$3,-1); // op2 <- -1 until patch
					nb_line=nb_ins; //The line of the JMF in the ASM file

				  }
	 body_void               {     //END of the WHILE Body
					patch(nb_line,get_ins_number()+1); //patches JMF to go to JMP
					int nb_ins = add_operation(JMP,-1,-1,-1);// op2 <- -1 until patch
					nb_line=nb_ins; //The line of the JMP in the ASM file
				 }
	;

if : tIF tLPAR exp tRPAR  {
				int nb_ins = add_operation(JMF,-1,$3,-1); // op2 <- -1 until patch
				nb_line=nb_ins; //The line of the JMF in the ASM file

			  }
     body_void 		  {     //END of the FIRST block
    				patch(nb_line,get_ins_number()+1); //patches JMF to go to JMP
     				int nb_ins = add_operation(JMP,-1,-1,-1);// op2 <- -1 until patch
     				nb_line=nb_ins; //The line of the JMP in the ASM file

		 	 }
     else
   ;

else :  %empty
	| tELSE body_void     {
				     //END of the SECOND block
				     patch(nb_line,get_ins_number()); //patches JMP to go out of Body 2
     			      }
        ;


declares : tINT declare declares1
	;

declares1 : %empty 
          | tCOMMA declare declares1
          ;

declare : tID                              {
                                              push($1,"int",0); //declared, not assigned
                                            }
         | tID tASSIGN exp                  {
                                              push($1,"int",1);
                                              int addr = get_addr($1);
				              add_operation(MOV,addr,$3,-1);
                                            }
	  ;

assign : tID tASSIGN exp   {
				int addr = get_addr($1);
				add_operation(MOV,addr,$3,-1);
			   }
	 ;

call : tID tLPAR args tRPAR
     | tID tLPAR tRPAR
     ;

args : exp
     | args tCOMMA exp
     ;


exp   :  tNB		{
				int addr = push("TMP","int",0); //temp var + get addr
				add_operation(MOV,addr,$1,-1);
				$$=addr;
				pop();

			}
       | tID            {	int addr = get_addr($1);
				$$ = addr;
			}
       | call           {
				printf("CALL \n"); //TODO
			}
       | exp tAND exp  {
       				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(AND,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tOR exp    {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(OR,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tADD exp   {	int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(ADD,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tSUB exp   {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(SUB,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tMUL exp   {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(MUL,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tDIV exp   {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(DIV,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tLT exp    {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(LT,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tLE exp    {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(LE,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tGT exp    {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(GT,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tGE exp    {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(GE,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tEQ exp    {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(EQ,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | exp tNE exp    {
				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(NE,addr_tmp,$1,$3);
				$$ = addr_tmp;
				pop();
			}
       | tNO exp %prec NOT {
       				int addr_tmp = push("TMP","int",0); //temp var + get addr_tmp
				add_operation(NO,addr_tmp,$2,-1);
				$$ = addr_tmp;
				pop();
			    }
       ;




%%

extern char *yytext;

void yyerror(const char *msg) {
  fprintf(stderr, "error: %s : Unexpected token near --> %s\n", msg, yytext);
  exit(1);
}

int main(void) {
  yyparse();
  return 0;
}
