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
    struct {
    	int condition;
    	int exit;
    } while_s;
}

%token <numD>  tNB
%token tINT tVOID
%token <name> tID
%token tCOMMA tSEMI 
%token tRETURN tPRINT
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

%token<numD> tIF
%token<numD> tELSE
%token<while_s> tWHILE

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

while  : tWHILE tLPAR   {
				$1.condition = get_ins_number()+1; //get where to start evaluating condition
			}

	 exp tRPAR 	{
				$1.exit = add_operation(JMF,-1,$4,-1); // op2 <- -1 until patch

			 }
	 body_void       {     //END of the WHILE Body
				patch($1.exit,get_ins_number()+2); //patches JMF to go to JMP
				add_operation(JMP,-1,-1,$1.condition);// op2 <- re-evaluate condition
			 }
	;

if : tIF tLPAR exp tRPAR  {
				int nb_ins = add_operation(JMF,-1,$3,-1); // op2 <- -1 until patch
				$1 = nb_ins;

			  }
     body_void 		  {     //END of the FIRST block
    				patch($1,get_ins_number()+2); //patches JMF to go to JMP
				$1=get_ins_number()+1; //The line of the JMP in the ASM file
		 	 }
     else
   ;

else :  %empty
	| tELSE               {
					int nb_ins = add_operation(JMP,-1,-1,-1);// op2 <- -1 until patch
					$1=nb_ins; //The line of the JMP in the ASM file

			      }
	  body_void           {
				     //END of the SECOND block
				     patch($1,get_ins_number()+1); //patches JMP to go out of Body 2
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
				add_operation(MVL,addr,$1,-1); //move value
				$$=addr;
				pop();

			}
       | tID            {	int addr = push("TMP","int",0); //temp var + get addr
				add_operation(MOV,addr,get_addr($1),-1); //move addr
				$$=addr;
			}
       | call           {
				printf("CALL \n"); //TODO
			}
       | exp tAND exp  {
       				add_operation(AND,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tOR exp    {
				add_operation(OR,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tADD exp   {
				add_operation(ADD,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tSUB exp   {
				add_operation(SUB,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tMUL exp   {
				add_operation(MUL,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tDIV exp   {
				add_operation(DIV,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tLT exp    {
				add_operation(LT,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tLE exp    {
				add_operation(LE,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tGT exp    {
				add_operation(GT,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tGE exp    {
				add_operation(GE,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tEQ exp    {
				add_operation(EQ,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | exp tNE exp    {
				add_operation(NE,$1,$1,$3);
				$$ = $1;
				pop();
			}
       | tNO exp %prec NOT {
				add_operation(NO,$2,$2,-1);
				$$ = $2;
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
