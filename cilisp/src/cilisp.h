#ifndef __cilisp_h_
#define __cilisp_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "parser.h"


#define NAN_RET_VAL (RET_VAL){DOUBLE_TYPE, NAN}
#define ZERO_RET_VAL (RET_VAL){INT_TYPE, 0}


#define BISON_FLEX_LOG_PATH "../src/bison-flex-output/bison_flex_log"
FILE* read_target;
FILE* flex_bison_log_file;


int yyparse(void);
int yylex(void);
void yyerror(char *, ...);
void warning(char*, ...);


typedef enum func_type {
    NEG_FUNC,
    ABS_FUNC,
    ADD_FUNC,
    SUB_FUNC,
    MULT_FUNC,
    DIV_FUNC,
    REMAINDER_FUNC,
    EXP_FUNC,
    EXP2_FUNC,
    POW_FUNC,
    LOG_FUNC,
    SQRT_FUNC,
    CBRT_FUNC,
    HYPOT_FUNC,
    MAX_FUNC,
    MIN_FUNC,
    RAND_FUNC,
    READ_FUNC,
    EQUAL_FUNC,
    LESS_FUNC,
    GREATER_FUNC,
    PRINT_FUNC,
    // TODO complete the enum
    CUSTOM_FUNC
} FUNC_TYPE;


FUNC_TYPE resolveFunc(char *);


typedef enum num_type {
    INT_TYPE,
    DOUBLE_TYPE,
    NO_TYPE
} NUM_TYPE;

NUM_TYPE resolveNumType(char *);

typedef struct {
    NUM_TYPE type;
    double value;
} AST_NUMBER;

typedef AST_NUMBER RET_VAL;

typedef struct {
    char* id;
} AST_SYMBOL;

typedef struct {
    struct ast_node *child;
} AST_SCOPE;

typedef struct ast_function {
    FUNC_TYPE func;
    struct ast_node *opList;
    char *ident;
} AST_FUNCTION;

typedef struct {
    struct ast_node *expr1;
    struct ast_node *expr2;
    struct ast_node *expr3;
} AST_COND;


typedef enum ast_node_type {
    NUM_NODE_TYPE,
    FUNC_NODE_TYPE,
    SYM_NODE_TYPE,
    SCOPE_NODE_TYPE,
    COND_NODE_TYPE
} AST_NODE_TYPE;

//typedef enum {
//    VAR_TYPE,
//    LAMBDA_TYPE,
//    ARG_TYPE
//} SYMBOL_TYPE;

typedef struct ast_node {
    AST_NODE_TYPE type;
    struct ast_node *parent;
    struct symbol_table_node *symbolTable;
    union {
        AST_NUMBER number;
        AST_FUNCTION function;
        AST_SYMBOL symbol;
        AST_SCOPE scope;
        AST_COND cond;
    } data;
    struct ast_node *next;
} AST_NODE;

//typedef struct stack_node {
//    RET_VAL value;
//    struct stack_node *next;
//} STACK_NODE;

typedef struct symbol_table_node {
    char *id;
    //SYMBOL_TYPE symbolType;
    NUM_TYPE type;
    AST_NODE *value;
    struct symbol_table_node *next;
    //struct stack_node *stack;
} SYMBOL_TABLE_NODE;

AST_NODE *createNumberNode(double value, NUM_TYPE type);
AST_NODE *createFunctionNode(FUNC_TYPE func, AST_NODE *opList);
AST_NODE  *createSymbolNode(char *name);
SYMBOL_TABLE_NODE *defineSymbol(char *name, AST_NODE *expr, NUM_TYPE type);
SYMBOL_TABLE_NODE *createLetList(SYMBOL_TABLE_NODE *let_elem, SYMBOL_TABLE_NODE *let_list);
AST_NODE *createScopeNode(SYMBOL_TABLE_NODE *let_sec, AST_NODE *s_expr);
AST_NODE *addExpressionToList(AST_NODE *newExpr, AST_NODE *exprList);
AST_NODE *createConditionNode(AST_NODE *expr1, AST_NODE *expr2, AST_NODE *expr3);

RET_VAL eval(AST_NODE *node);

void printRetVal(RET_VAL val);

void freeNode(AST_NODE *node);

#endif
