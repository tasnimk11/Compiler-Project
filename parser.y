%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "sym_tab.h"
 
%}


%code provides {
  int yylex (void);
  void yyerror (const char *);
}

%union{
    int  numD;
    char *numX;
    char *name;
}

%token <numX,numD>  tNB tNB_D tNB_X t_NB
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

%token tIF tELSE 
%nonassoc LOWER_THAN_ELSE

%token tASSIGN 



%%

prog : funs ;

funs : funs fun 
     | fun ;

fun : header_int  body_int 
    | header_void body_void ; 

header_void : tVOID tID tLPAR params tRPAR ;

header_int : tINT tID tLPAR params tRPAR ;

params : params tCOMMA param
       | unique_param ;

param : tINT tID;

unique_param : tINT tID 
             | tVOID 
             | ;

body_void : tLBRACE ins tRBRACE ;

body_int : tLBRACE ins return tRBRACE;

return : tRETURN exp tSEMI ;



ins : in ins 
    | ; 

in : print tSEMI
   | while 
   | if 
   | declare tSEMI
   | assign tSEMI
   | call tSEMI;

print : tPRINT tLPAR exp tRPAR ;

while  : tWHILE tLPAR exp tRPAR body_void ;

if : tIF tLPAR exp tRPAR body_void %prec LOWER_THAN_ELSE;
   | tIF tLPAR exp tRPAR body_void tELSE body_void ;

declare : tINT declares;

declares : tID                              {
                                              push($1,"int",0,1,0); //declared, not assigned 
                                            } 
         | tID tASSIGN exp                  {
                                              push($1,"int",1,1,0); 
                                            } 
         | declares tCOMMA tID              {
                                              push($3,"int",0,1,0); 
                                            } 
         | declares tCOMMA tID tASSIGN call {
                                              push($3,"int",0,1,0); 
                                            } ;

assign : tID tASSIGN exp
       | tID tASSIGN call 

call : tID tLPAR args tRPAR 
     | tID tLPAR tRPAR ;

args : exp
     | args tCOMMA exp ;

value_exp : tNB 
          | tNB_D 
          | tNB_X 
          | tID;

exp    : value_exp 
       | exp tAND exp 
       | exp tOR exp 
       | exp tADD exp 
       | exp tSUB exp 
       | exp tMUL exp 
       | exp tDIV exp 
       | exp tLT exp 
       | exp tLE exp 
       | exp tGT exp 
       | exp tGE exp 
       | exp tEQ exp
       | exp tNE exp
       | tNO exp %prec NOT;


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
