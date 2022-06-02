#include "parse.h"
#include <stdarg.h>

TOKEN *getNextToken(TOKEN **token)
{
    freeToken(token);
    TOKEN* tok = scanner();
    // uncomment the line below if desired for debugging purposes.
    //printToken(&tok); fflush(stdout);
    return tok;
}

NODE *program()
{
    NODE *node = calloc(sizeof(NODE), 1);
    node->type = PROGRAM_NODE;
    node->leftChild = statement();
    if (node->leftChild != NULL)
    {
        node->rightChild = program();
    }
    else
    {
        free(node);
        node = NULL;
    }
    return node;
}

NODE *statement()
{
    TOKEN *token = getNextToken(NULL);
    if (token == NULL)
    {
        return NULL;
    }
    else if (token->type == EOF_TOKEN)
    {
        freeToken(&token);
        return NULL;
    }

    NODE *node = calloc(sizeof(NODE), 1);
    node->type = STATEMENT_NODE;

    switch(token->type)
    {
        case IDENT_TOKEN:
            node->leftChild = assignStmt(&token);
            break;
        case REPEAT_TOKEN:
            node->leftChild = repeatStmt(&token);
            break;
        case PRINT_TOKEN:
            node->leftChild = printStmt(&token);
            break;
        default:
            // see the TOKEN_TYPE enum to see which numbers mean what...
            error("Invalid token at start of statement : ");
            printToken(&token);
            break;
    }

    return node;
}

NODE *assignStmt(TOKEN **currToken)
{
    NODE *node = calloc(sizeof(NODE), 1);
    node->type = ASSIGN_STMT_NODE;

    node->leftChild = ident(currToken);

    *currToken = getNextToken(currToken);
    if((*currToken)->type != ASSIGNMENT_TOKEN)
    {
        //printToken(currToken);
        error("Expected assignment token in assignment statement.");
    }

    *currToken = getNextToken(currToken);
    node->rightChild = expr(currToken);

    *currToken = getNextToken(currToken);
    if((*currToken)->type != SEMICOLON_TOKEN)
    {
        error("Expected semicolon token in assignment statement.");
    }

    freeToken(currToken);
    // TODO
    return node;
}

NODE *repeatStmt(TOKEN **currToken)
{
    NODE *node = calloc(sizeof(NODE), 1);
    node->type = REPEAT_STMT_NODE;

    *currToken = getNextToken(currToken);
    if((*currToken)->type != LPAREN_TOKEN)
    {
        error("Expected left paren token in repeat statement.");
    }

    *currToken = getNextToken(currToken);
    node->leftChild = expr(currToken);

    *currToken = getNextToken(currToken);
    if((*currToken)->type != RPAREN_TOKEN)
    {
        error("Expected right paren token in repeat statement.");
    }

    freeToken(currToken);
    node->rightChild = statement();

    // TODO
    return node;
}

NODE *printStmt(TOKEN **currToken)
{
    NODE *node = calloc(sizeof(NODE), 1);
    node->type = PRINT_STMT_NODE;

    *currToken = getNextToken(currToken);
    if((*currToken)->type != LPAREN_TOKEN)
    {
        error("Expected left paren token in print statement.");
    }

    *currToken = getNextToken(currToken);
    node->leftChild = expr(currToken);

    *currToken = getNextToken(currToken);
    if((*currToken)->type != RPAREN_TOKEN)
    {
        error("Expected right paren token in print statement.");
    }

    *currToken = getNextToken(currToken);
    if((*currToken)->type != SEMICOLON_TOKEN)
    {
        error("Expected semicolon token in print statement.");
    }
    freeToken(currToken);
    // TODO
    return node;
}

NODE *expr(TOKEN **currToken)
{
    NODE *node = calloc(sizeof(NODE), 1);
    node->type = EXPR_NODE;

    node->leftChild = term(currToken);

    *currToken = getNextToken(currToken);
    if((*currToken)->type == ADD_OP_TOKEN)
    {
        node->data.op = (*currToken)->val.op;
        *currToken = getNextToken(currToken);
        node->rightChild = expr(currToken);
    }
    else
    {
        node->rightChild = NULL;
        ungetToken(currToken);
    }

    // TODO
    return node;
}

NODE *term(TOKEN **currToken)
{
    NODE *node = calloc(sizeof(NODE), 1);
    node->type = TERM_NODE;

    node->leftChild = factor(currToken);

    *currToken = getNextToken(currToken);
    if((*currToken)->type == MULT_OP_TOKEN)
    {
        node->data.op = (*currToken)->val.op;
        *currToken = getNextToken(currToken);
        node->rightChild = term(currToken);
    }
    else
    {
        node->rightChild = NULL;
        ungetToken(currToken);
    }

    // TODO
    return node;
}

NODE *factor(TOKEN **currToken)
{
    NODE *node = calloc(sizeof(NODE), 1);
    node->type = FACTOR_NODE;

    switch ((*currToken)->type)
    {
        case IDENT_TOKEN:
            node->leftChild = ident(currToken);
            node->rightChild = NULL;
            break;
        case INT_TOKEN:
        case FLOAT_TOKEN:
            node->leftChild = number(currToken);
            node->rightChild = NULL;
            break;
        case ADD_OP_TOKEN:
            node->data.op = (*currToken)->val.op;
            node->rightChild = NULL;
            *currToken = getNextToken(currToken);
            node->leftChild = factor(currToken);
            break;
        case LPAREN_TOKEN:
            *currToken = getNextToken(currToken);
            node->leftChild = expr(currToken);
            node->rightChild = NULL;
            *currToken = getNextToken(currToken);
            if((*currToken)->type != RPAREN_TOKEN)
            {
                error("Expected right paren in factor statement.");
            }
            freeToken(currToken);
            break;
        default:
            error("Invalid token in factor statement.");
            break;
    }

    // TODO
    return node;
}

NODE *ident(TOKEN **currToken)
{
    NODE *node = calloc(sizeof(NODE), 1);
    node->type = IDENT_NODE;
    node->data.identifier = calloc(sizeof(char), strlen((*currToken)->val.string)+1);
    strcpy(node->data.identifier, (*currToken)->val.string);
    // TODO
    return node;
}

NODE *number(TOKEN **currToken)
{
    NODE *node = calloc(sizeof(NODE), 1);
    node->type = NUMBER_NODE;

    if((*currToken)->type == INT_TOKEN)
    {
        node->data.number.type = INT_TYPE;
        node->data.number.value.integral = (*currToken)->val.integral;
    }
    else
    {
        node->data.number.type = FLOAT_TYPE;
        node->data.number.value.floating_point = (*currToken)->val.floating_point;
    }
    // TODO
    return node;
}

void freeParseTree(NODE **node)
{
    if (node == NULL)
    {
        return;
    }

    if ((*node) == NULL)
    {
        return;
    }

    if((*node)->leftChild != NULL)
        freeParseTree(&(*node)->leftChild);

    if((*node)->rightChild != NULL)
        freeParseTree(&(*node)->rightChild);

    if ((*node)->type == IDENT_NODE)
    {
        free((*node)->data.identifier);
    }

    free(*node);
    *node = NULL;
}

void error(char *errorFormat, ...)
{
    char buffer[256];
    va_list args;
    va_start (args, errorFormat);
    vsnprintf (buffer, 255, errorFormat, args);

    printf("\nPARSING ERROR: %s\nExiting...\n", buffer);

    va_end (args);
    exit(1);
}
