/*
 * Christopher Valencia
 * scanner 1 project
 * 9/30/2020
 */
#ifndef __SCANNER_H
#define __SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    UNASSIGNED,
    INVALID_TOKEN,
    EOF_TOKEN,
    LPAREN,
    RPAREN,
    ASSIGN,
    ID,
    INT,
    FLT,
    ADDOP,
    MULTOP,
    SCOLON,
    PRINT,
    REPEAT
    // TODO complete the enum
    // there are 11 more...
} TOKEN_TYPE;

typedef union
{
    long integer;
    double floating_point;
    char *string;
    char op;
} TOKEN_VALUE;

typedef struct token
{
    TOKEN_TYPE type;
    TOKEN_VALUE val;
} TOKEN;

typedef enum
{
    START_STATE,
    INVALID_STATE,
    LPAREN_STATE,
    RPAREN_STATE,
    ASSIGN_STATE,
    ID_STATE,
    INT_STATE,
    FLT_STATE,
    ADDOP_STATE,
    MULTOP_STATE,
    SCOLON_STATE,
    EOF_STATE
    // TODO complete the enum
    // Recall that identifiers and keywords share a state.
} FSM_STATE;

TOKEN *scanner();
void freeToken(TOKEN **);
void printToken(TOKEN **);

#endif