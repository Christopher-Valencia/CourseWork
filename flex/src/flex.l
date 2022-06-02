/* NOTE: % must be in the first column (no indentation) */
/* TODO add more regular expressions and returns for the other TOKEN types */


%option noyywrap
%option nounput
%option noinput

%{
   #include "flex.h"
%}

letter          [a-zA-Z_$]
digit           [0-9]

while           (while)
if              (if)
repeat          (repeat)
print           (print)

float           {digit}+\.{digit}*
ident           {letter}({digit}|{letter})*
int             {digit}*


%%

while       {return WHILE_TOKEN;}
if          {return IF_TOKEN;}
repeat      {return REPEAT_TOKEN;}
print       {return PRINT_TOKEN;}

{float}     {return FLOAT_TOKEN;}
{ident}     {return IDENT_TOKEN;}
{int}       {return INT_TOKEN;}

[+-]        {return ADDOP_TOKEN;}
[*/%]       {return MULTOP_TOKEN;}

;           {return SCOLON_TOKEN;}
=           {return ASSIGN_TOKEN;}
\(          {return LPAREN_TOKEN;}
\)          {return RPAREN_TOKEN;}

<<EOF>>     {return EOF_TOKEN;}
[ \n\r\t]   ; //skip whitespace
.           {printf("ERROR: invalid character: >>%s<<\n", yytext);}

%%

