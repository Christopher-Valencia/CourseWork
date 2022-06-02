#include "print.h"

void printProgram(NODE *node, int indent)
{
    if (node == NULL)
    {
        return;
    }

    if (node->leftChild != NULL)
    {
        printStatement(node->leftChild, indent);
    }
    if (node->rightChild != NULL)
    {
        printProgram(node->rightChild, indent);
    }
}

void printStatement(NODE *node, int indent)
{
    printfIndented(indent, "START STATEMENT");

    if(node->leftChild != NULL)
    {
        switch (node->leftChild->type)
        {
            case ASSIGN_STMT_NODE:
                printAssignStmt(node->leftChild, indent + 1);
                break;
            case REPEAT_STMT_NODE:
                printRepeatStmt(node->leftChild, indent + 1);
                break;
            case PRINT_STMT_NODE:
                printPrintStmt(node->leftChild, indent + 1);
                break;
            default:
                error("Child of statement node has invalid type cannot print.");
                break;
        }
    }
    printfIndented(indent, "END STATEMENT");
}

void printAssignStmt(NODE *node, int indent)
{
    printfIndented(indent, "START ASSIGN STATEMENT");

    printId(node->leftChild, indent+1);
    printExpr(node->rightChild, indent+1);

    printfIndented(indent, "END ASSIGN STATEMENT");
    // TODO
}

void printRepeatStmt(NODE *node, int indent)
{
    printfIndented(indent, "START REPEAT STATEMENT");

    printExpr(node->leftChild, indent+1);
    printStatement(node->rightChild, indent+1);

    printfIndented(indent, "END REPEAT STATEMENT");
    // TODO
}

void printPrintStmt(NODE *node, int indent)
{
    printfIndented(indent, "START PRINT STATEMENT");

    printExpr(node->leftChild, indent+1);

    printfIndented(indent, "END PRINT STATEMENT");
    // TODO
}

void printExpr(NODE *node, int indent)
{
    printfIndented(indent, "START EXPRESSION");

    printTerm(node->leftChild, indent+1);
    if(node->rightChild != NULL)
    {
        printfIndented(indent, "<ADDOP %c>", node->data.op);
        printExpr(node->rightChild, indent+1);
    }

    printfIndented(indent, "END EXPRESSION");
    // TODO
}

void printTerm(NODE *node, int indent)
{
    printfIndented(indent, "START TERM");

    printFactor(node->leftChild, indent+1);
    if(node->rightChild != NULL)
    {
        printfIndented(indent, "<MULTOP %c>", node->data.op);
        printTerm(node->rightChild, indent+1);
    }

    printfIndented(indent, "END TERM");

    // TODO
}

void printFactor(NODE *node, int indent)
{
    printfIndented(indent, "START FACTOR");

    switch (node->leftChild->type)
    {
        case IDENT_NODE:
            printId(node->leftChild, indent+1);
            break;
        case NUMBER_NODE:
            printNumber(node->leftChild, indent+1);
            break;
        case FACTOR_NODE:
            printfIndented(indent, "<ADDOP %c>", node->data.op);
            printFactor(node->leftChild, indent+1);
            break;
        case EXPR_NODE:
            printExpr(node->leftChild, indent+1);
            break;
    }

    printfIndented(indent, "END FACTOR");
    // TODO
}

void printId(NODE *node, int indent)
{
    printfIndented(indent, "START IDENT");

    printfIndented(indent+1, node->data.identifier);

    printfIndented(indent, "END IDENT");
    // TODO
}

void printNumber(NODE *node, int indent)
{
    printfIndented(indent, "START NUMBER");

    if(node->data.number.type == INT_TYPE)
        printfIndented(indent+1, "INT: %i", node->data.number.value.integral);
    else
        printfIndented(indent+1, "FLOAT : %lf", node->data.number.value.floating_point);

    printfIndented(indent, "END NUMBER");
    // TODO
}

void printfIndented(int indent, char *format, ...)
{
    printf("\n");

    for (int i = 0; i < indent; ++i)
    {
        printf("|  ");
    }

    char buffer[256];
    va_list args;
    va_start (args, format);
    vsnprintf (buffer, 255, format, args);

    printf("%s", buffer);

    va_end (args);
}

