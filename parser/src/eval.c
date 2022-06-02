#include "eval.h"
#include <math.h>

#define NAN_NUMBER (NUMBER){FLOAT_TYPE, .value.floating_point = NAN}
#define DEFAULT_NUMBER (NUMBER){INT_TYPE, 0}


SYMBOL_TABLE_NODE *symbolTable = NULL;

void evalProgram(NODE *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->leftChild != NULL)
    {
        evalStatement(node->leftChild);
    }

    if (node->rightChild != NULL)
    {
        evalProgram(node->rightChild);
    }
}

void evalStatement(NODE *node)
{
    if (node->leftChild != NULL)
    {
        //printf("statement %d\n", node->leftChild->type);
        switch (node->leftChild->type)
        {
            case ASSIGN_STMT_NODE:
                evalAssignStmt(node->leftChild);
                break;
            case REPEAT_STMT_NODE:
                evalRepeatStmt(node->leftChild);
                break;
            case PRINT_STMT_NODE:
                evalPrintStmt(node->leftChild);
                break;
            default:
                error("Invalid child of type %d in statement node.", node->leftChild->type);
        }
    }
}

void evalAssignStmt(NODE *node)
{
    if(findSymbol(symbolTable, node->leftChild->data.identifier) == NULL)
    {
        if(symbolTable == NULL)
            symbolTable = createSymbol(node->leftChild->data.identifier, evalExpr(node->rightChild));
        else
            addSymbolToTable(&symbolTable, createSymbol(node->leftChild->data.identifier, evalExpr(node->rightChild)));
    }
    else
    {
        reassignSymbol(findSymbol(symbolTable, node->leftChild->data.identifier), evalExpr(node->rightChild));
    }
    // TODO
}

void evalRepeatStmt(NODE *node)
{
    if(node->leftChild->leftChild->leftChild->leftChild->data.number.type == INT_TYPE)
    {
        for(int x = 0; x < node->leftChild->leftChild->leftChild->leftChild->data.number.value.integral; x++)
        {
            evalStatement(node->rightChild);
        }
    }
    else
    {
        for(int x = 0; x < (int)(node->leftChild->leftChild->leftChild->leftChild->data.number.value.floating_point); x++)
        {
            evalStatement(node->rightChild);
        }
    }

    // TODO
}

void evalPrintStmt(NODE *node)
{
    if(evalExpr(node->leftChild).type == INT_TYPE)
        printf("INT : %li\n", evalExpr(node->leftChild).value.integral);
    else
        printf("FLOAT : %lf\n", evalExpr(node->leftChild).value.floating_point);
    // TODO
}

NUMBER evalExpr(NODE *node)
{
    // TODO
    if(node->rightChild == NULL)
        return(evalTerm(node->leftChild));
    else if(node->rightChild != NULL)
        return(evalOperation(evalTerm(node->leftChild), evalExpr(node->rightChild), node->data.op));

    return DEFAULT_NUMBER;
}

NUMBER evalTerm(NODE *node)
{
    if(node->rightChild == NULL)
        return(evalFactor(node->leftChild));
    else if(node->rightChild != NULL)
        return(evalOperation(evalFactor(node->leftChild), evalTerm(node->rightChild), node->data.op));

    // TODO
    return DEFAULT_NUMBER;
}

NUMBER evalFactor(NODE *node)
{
    if(node->leftChild->type == IDENT_NODE)
        return(evalId(node->leftChild));
    else if(node->leftChild->type == NUMBER_NODE)
        return(evalNumber(node->leftChild));
    else if(node->leftChild->type == EXPR_NODE)
        return(evalExpr(node->leftChild));
    else if(node->leftChild->type == FACTOR_NODE)
        return(evalFactor(node->leftChild));

    // TODO
    return DEFAULT_NUMBER;
}

NUMBER evalNumber(NODE *node)
{
    if(node != NULL)
        return(node->data.number);
    // TODO
    return DEFAULT_NUMBER;
}

NUMBER evalId(NODE *node)
{
    if(findSymbol(symbolTable, node->data.identifier) != NULL)
        return(findSymbol(symbolTable, node->data.identifier)->value);
    // TODO
    return DEFAULT_NUMBER;
}

NUMBER evalAdd(NUMBER op1, NUMBER op2)
{
    if(op1.type == INT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.integral = op1.value.integral + op2.value.integral;
        return(op1);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == FLOAT_TYPE)
    {
        op1.value.floating_point = op1.value.floating_point + op2.value.floating_point;
        return(op1);
    }
    else if(op1.type == INT_TYPE && op2.type == FLOAT_TYPE)
    {
        op2.value.floating_point = op1.value.integral + op2.value.floating_point;

        return(op2);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.floating_point = op1.value.floating_point + op2.value.integral;
        return(op1);
    }
    // TODO
    return DEFAULT_NUMBER;
}

NUMBER evalSub(NUMBER op1, NUMBER op2)
{
    if(op1.type == INT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.integral = op1.value.integral - op2.value.integral;
        return(op1);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == FLOAT_TYPE)
    {
        op1.value.floating_point = op1.value.floating_point - op2.value.floating_point;
        return(op1);
    }
    else if(op1.type == INT_TYPE && op2.type == FLOAT_TYPE)
    {
        op2.value.floating_point = op1.value.integral - op2.value.floating_point;
        return(op2);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.floating_point = op1.value.floating_point - op2.value.integral;
        return(op1);
    }
    // TODO
    return DEFAULT_NUMBER;
}

NUMBER evalMult(NUMBER op1, NUMBER op2)
{
    if(op1.type == INT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.integral = op1.value.integral * op2.value.integral;
        return(op1);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == FLOAT_TYPE)
    {
        op1.value.floating_point = op1.value.floating_point * op2.value.floating_point;
        return(op1);
    }
    else if(op1.type == INT_TYPE && op2.type == FLOAT_TYPE)
    {
        op2.value.floating_point = op1.value.integral * op2.value.floating_point;
        return(op2);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.floating_point = op1.value.floating_point * op2.value.integral;
        return(op1);
    }
    // TODO
    return DEFAULT_NUMBER;
}

NUMBER evalDiv(NUMBER op1, NUMBER op2)
{
    if(op1.type == INT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.integral = op1.value.integral / op2.value.integral;
        return(op1);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == FLOAT_TYPE)
    {
        op1.value.floating_point = op1.value.floating_point / op2.value.floating_point;
        return(op1);
    }
    else if(op1.type == INT_TYPE && op2.type == FLOAT_TYPE)
    {
        op2.value.floating_point = op1.value.integral / op2.value.floating_point;
        return(op2);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.floating_point = op1.value.floating_point / op2.value.integral;
        return(op1);
    }
    // TODO
    return DEFAULT_NUMBER;
}

NUMBER evalMod(NUMBER op1, NUMBER op2)
{
    if(op1.type == INT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.integral = op1.value.integral % op2.value.integral;
        return(op1);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == FLOAT_TYPE)
    {
        op1.value.floating_point = fmod(op1.value.floating_point, op2.value.floating_point);
        return(op1);
    }
    else if(op1.type == INT_TYPE && op2.type == FLOAT_TYPE)
    {
        op2.value.floating_point = fmod(op1.value.integral, op2.value.floating_point);
        return(op2);
    }
    else if(op1.type == FLOAT_TYPE && op2.type == INT_TYPE)
    {
        op1.value.floating_point = fmod(op1.value.floating_point, op2.value.integral);
        return(op1);
    }
    // TODO
    return DEFAULT_NUMBER;
}

NUMBER evalOperation(NUMBER operand1, NUMBER operand2, char op)
{
    switch (op)
    {
        case '+':
            return evalAdd(operand1, operand2);
        case '-':
            return evalSub(operand1, operand2);
        case '*':
            return evalMult(operand1, operand2);
        case '/':
            return evalDiv(operand1, operand2);
        case '%':
            return evalMod(operand1, operand2);
        default:
            error("Invalid operation character %c.", op);
    }
    return DEFAULT_NUMBER; // unreachable
}

SYMBOL_TABLE_NODE *findSymbol(SYMBOL_TABLE_NODE *table, char *ident)
{
    while (table != NULL)
    {
        if (strcmp(ident, table->ident) == 0)
        {
            return table;
        }
        table = table->next;
    }
    return NULL;
}

SYMBOL_TABLE_NODE *createSymbol(char *ident, NUMBER value)
{
    SYMBOL_TABLE_NODE *newSymbol = calloc(sizeof(SYMBOL_TABLE_NODE), 1);
    newSymbol->ident = calloc(sizeof(char), strlen(ident)+1);
    strcpy(newSymbol->ident, ident);
    newSymbol->value = value;
    return newSymbol;
}

void reassignSymbol(SYMBOL_TABLE_NODE* symbol, NUMBER value)
{
    symbol->value = value;
}

void addSymbolToTable(SYMBOL_TABLE_NODE **table, SYMBOL_TABLE_NODE *newSymbol)
{
    newSymbol->next = *table;
    *table = newSymbol;
}

NUMBER evalSymbol(SYMBOL_TABLE_NODE *symbol)
{
    return symbol->value;
}

void freeSymbolTable(SYMBOL_TABLE_NODE **table)
{
    if (table == NULL)
    {
        return;
    }
    if (*table == NULL)
    {
        return;
    }

    freeSymbolTable(&(*table)->next);
    free((*table)->ident);
    free(*table);
    *table = NULL;
}

void cleanUpSymbolTables()
{
    freeSymbolTable(&symbolTable);
}
