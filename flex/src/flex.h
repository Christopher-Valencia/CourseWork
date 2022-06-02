#ifndef __flex_h_
#define __flex_h_

#include <stdio.h>

// TODO complete the TOKEN enum
typedef enum {
    EOF_TOKEN,
    IF_TOKEN,
    FLOAT_TOKEN,
    IDENT_TOKEN,
    ASSIGN_TOKEN,
    WHILE_TOKEN,
    REPEAT_TOKEN,
    PRINT_TOKEN,
    INT_TOKEN,
    ADDOP_TOKEN,
    MULTOP_TOKEN,
    LPAREN_TOKEN,
    RPAREN_TOKEN,
    SCOLON_TOKEN
    //etc
} TOKEN;

int yylex(void);
void yyerror(char *s);

#endif
