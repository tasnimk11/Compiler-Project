%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%option nounput
%option noinput
%option yylineno
%option noyywrap


%x MCOMMENT


/*Decimal Number*/
tNB_D          ([0-9]+)              
/*Hexadecimal Number*/ 
tNB_X          (0[xX][0-9a-fA-F]+)                   


/*One Line Comment*/
LCOMMENT       ("//".*)


/*ID : starts with Letter followed by any number of alphabetic letters and digits*/
ID             [a-zA-Z][0-9a-zA-Z]*



%%

"int"             {return tINT;}

{tNB_D}       	  { yylval.numD=atoi(yytext);
                    return tNB;}                                /*Num -> Hexa*/
{tNB_X}           { yylval.numD = strtol(yytext, NULL ,16);
                    return tNB;}                                /*Hexa -> Num*/

"print"            {return tPRINT;}
"return"           {return tRETURN;}
"void"             {return tVOID;}
"if"               {return tIF;}
"else"             {return tELSE;}
"while"            {return tWHILE;}

"#"[^\n]*           ;                                           /* Ignore preprocessor directives */


{LCOMMENT}          ;                                           /* ignores one line comments */

"/*"              BEGIN(MCOMMENT);                              /* ignores multiplr-line comments */
<MCOMMENT>[^*\n]*        ;                                      /* skips everything except for '*' */
<MCOMMENT>"*"+[^*/\n]*   ;                                      /* skips '*'that is not followed by '/'s */
<MCOMMENT>\n             ;                                      /* skips carrier return */
<MCOMMENT>"*"+"/"  BEGIN(INITIAL);

[ \t\n]+        ;                                               /* ignores whitespace */

{ID}      	   	{ strcpy(yylval.name, yytext);
                  return tID;}
                   
[+]             {return tADD;}
[-]             {return tSUB;}
[*]             {return tMUL;}
[/]             {return tDIV;}
[<]             {return tLT;}
[>]             {return tGT;}
[!][=]          {return tNE;}
[=][=]          {return tEQ;}
[>][=]          {return tGE;}
[<][=]          {return tLE;}
[=]             {return tASSIGN;}
[&][&]          {return tAND;}
[|][|]          {return tOR;}
[!]            {return tNO;}
[(]             {return tLPAR;}
[)]             {return tRPAR;}
[;]             {return tSEMI;}
[,]             {return tCOMMA;}
[}]             {return tRBRACE;}
[{]             {return tLBRACE;}
.               ;                                              /*default*/
