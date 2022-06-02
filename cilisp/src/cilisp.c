#include "cilisp.h"
#include <time.h>

#define RED             "\033[31m"
#define RESET_COLOR     "\033[0m"

// yyerror:
// Something went so wrong that the whole program should crash.
// You should basically never call this unless an allocation fails.
// (see the "yyerror("Memory allocation failed!")" calls and do the same.
// This is basically printf, but red, with "\nERROR: " prepended, "\n" appended,
// and an "exit(1);" at the end to crash the program.
// It's called "yyerror" instead of "error" so the parser will use it for errors too.
void yyerror(char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsnprintf (buffer, 255, format, args);

    printf(RED "\nERROR: %s\nExiting...\n" RESET_COLOR, buffer);
    fflush(stdout);

    va_end (args);
    exit(1);
}

// warning:
// Something went mildly wrong (on the user-input level, probably)
// Let the user know what happened and what you're doing about it.
// Then, move on. No big deal, they can enter more inputs. ¯\_(ツ)_/¯
// You should use this pretty often:
//      too many arguments, let them know and ignore the extra
//      too few arguments, let them know and return NAN
//      invalid arguments, let them know and return NAN
//      many more uses to be added as we progress...
// This is basically printf, but red, and with "\nWARNING: " prepended and "\n" appended.
void warning(char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsnprintf (buffer, 255, format, args);

    printf(RED "WARNING: %s\n" RESET_COLOR, buffer);
    fflush(stdout);

    va_end (args);
}

FUNC_TYPE resolveFunc(char *funcName)
{
    // Array of string values for function names.
    // Must be in sync with members of the FUNC_TYPE enum in order for resolveFunc to work.
    // For example, funcNames[NEG_FUNC] should be "neg"
    char *funcNames[] = {
            "neg",
            "abs",
            "add",
            "sub",
            "mult",
            "div",
            "remainder",
            "exp",
            "exp2",
            "pow",
            "log",
            "sqrt",
            "cbrt",
            "hypot",
            "max",
            "min",
            "rand",
            "read",
            "equal",
            "less",
            "greater",
            "print",
            // TODO complete the array
            // the empty string below must remain the last element
            ""
    };
    int i = 0;
    while (funcNames[i][0] != '\0')
    {
        if (strcmp(funcNames[i], funcName) == 0)
        {
            return i;
        }
        i++;
    }
    return CUSTOM_FUNC;
}

NUM_TYPE resolveNumType(char *numType)
{
    if(strcmp(numType, "int") == 0)
        return(INT_TYPE);
    else if(strcmp(numType, "double") == 0)
        return(DOUBLE_TYPE);
    else
        return(NO_TYPE);
}

AST_NODE *createNumberNode(double value, NUM_TYPE type)
{
    //warning("Number Created %lf", value);
    AST_NODE *node;
    size_t nodeSize;

    nodeSize = sizeof(AST_NODE);
    if ((node = calloc(nodeSize, 1)) == NULL)
    {
        yyerror("Memory allocation failed!");
        exit(1);
    }

    node->type = NUM_NODE_TYPE;
    node->data.number.type = type;
    node->data.number.value = value;
    //warning("NumberNode Value = %lf", node->data.number.value);

    // TODO complete the function
    // Populate "node", the AST_NODE * created above with the argument data.
    // node is a generic AST_NODE, don't forget to specify it is of type NUMBER_NODE

    return node;
}


AST_NODE *createFunctionNode(FUNC_TYPE func, AST_NODE *opList) {

    AST_NODE *node;
    size_t nodeSize;

    nodeSize = sizeof(AST_NODE);
    if ((node = calloc(nodeSize, 1)) == NULL) {
        yyerror("Memory allocation failed!");
        exit(1);
    }

    node->type = FUNC_NODE_TYPE;
    node->data.function.func = func;
    if (opList != NULL)
    {
        node->data.function.opList = opList;
        node->data.function.opList->parent = node;
        if(node->data.function.opList->next != NULL)
            node->data.function.opList->next->parent = node;
    }
    else
        node->data.function.opList = NULL;

    // TODO complete the function
    // Populate the allocated AST_NODE *node's data

    return node;
}



SYMBOL_TABLE_NODE *defineSymbol(char *name, AST_NODE *expr, NUM_TYPE type)
{
    SYMBOL_TABLE_NODE *table;

    if ((table = calloc(sizeof(SYMBOL_TABLE_NODE), 1)) == NULL)
    {
        yyerror("Memory allocation failed!");
        exit(1);
    }

    name = strtok(name, " ");
    //warning("symbol \"%s\" definded!", name);
    //printf("expr value: %lf\n", expr->data.number.value);
    //printf("symbol assigned to symbol \"%s\"\n", expr->data.symbol.id);

    table->id = calloc(sizeof(char), strlen(name)+1);
    strcpy(table->id, name);
    //table->value = malloc(sizeof(AST_NODE));
    table->value = expr;

    if(type != NO_TYPE)
        table->type = type;
    else
        table->type = NO_TYPE;

    return table;
}

AST_NODE  *createSymbolNode(char *name)
{
    AST_NODE  *node;
    size_t nodeSize;

    nodeSize = sizeof(AST_NODE);
    if ((node = calloc(nodeSize, 1)) == NULL)
    {
        yyerror("Memory allocation failed!");
        exit(1);
    }
    //warning("symbol \"%s\" created!", name);
    node->type = SYM_NODE_TYPE;
    node->data.symbol.id = calloc(sizeof(char), strlen(name)+1);
    strcpy(node->data.symbol.id, name);
    return node;
}

AST_NODE *createScopeNode(SYMBOL_TABLE_NODE *let_sec, AST_NODE *s_expr)
{
    AST_NODE  *node;
    size_t nodeSize;

    nodeSize = sizeof(AST_NODE);
    if ((node = calloc(nodeSize, 1)) == NULL)
    {
        yyerror("Memory allocation failed!");
        exit(1);
    }

    node->type = SCOPE_NODE_TYPE;
    node->data.scope.child = s_expr;
    node->data.scope.child->parent = node;

    /*if ((node->data.scope.child->symbolTable = calloc(sizeof(SYMBOL_TABLE_NODE), 1)) == NULL)
    {
        yyerror("Memory allocation failed!");
        exit(1);
    }*/

    node->data.scope.child->symbolTable = let_sec;
    node->data.scope.child->symbolTable->value->parent = node->data.scope.child;

    if(node->data.scope.child->symbolTable->next != NULL)
        node->data.scope.child->symbolTable->next->value->parent = node->data.scope.child;

    //warning("scope created!");
    return node;
}

SYMBOL_TABLE_NODE *createLetList(SYMBOL_TABLE_NODE *let_elem, SYMBOL_TABLE_NODE *let_list)
{
    if(strcmp(let_elem->id, let_list->id) != 0)
    {
        let_elem->next = let_list;
        //printf("first: %s; second: %s\n", let_elem->id, let_list->id);
        let_list->value->parent = let_elem->value->parent;
    }
    else
        warning("Duplicate assignment to symbol \"%s\" detected in the same scope!\nOnly the first assignment is kept!");
    //warning("let list created!");
    return let_elem;
}

AST_NODE *addExpressionToList(AST_NODE *newExpr, AST_NODE *exprList)
{
    newExpr->next = exprList;
    exprList->parent = newExpr->parent;
    return newExpr;
}

AST_NODE *createConditionNode(AST_NODE *expr1, AST_NODE *expr2, AST_NODE *expr3)
{
    AST_NODE  *node;
    size_t nodeSize;

    nodeSize = sizeof(AST_NODE);
    if ((node = calloc(nodeSize, 1)) == NULL)
    {
        yyerror("Memory allocation failed!");
        exit(1);
    }

    node->type = COND_NODE_TYPE;
    node->data.cond.expr1 = expr1;
    node->data.cond.expr2 = expr2;
    node->data.cond.expr3 = expr3;

    return node;
}

RET_VAL evalCondition(AST_NODE *node)
{
    if(!node->data.cond.expr1 || !node->data.cond.expr2 || !node->data.cond.expr3)
    {
        warning("Exactly 3 expressions not given! NAN returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;
    if(eval(node->data.cond.expr1).value != 0.0)
        result = eval(node->data.cond.expr2);
    else
        result = eval(node->data.cond.expr3);

    return result;
}

RET_VAL evalSymbol(AST_NODE *symbol)
{
    //printf("evalSymbol: %s\n", symbol->data.symbol.id);

    AST_NODE  *node;
//    size_t nodeSize;
//
//    nodeSize = sizeof(AST_NODE);
//    if ((node = calloc(nodeSize, 1)) == NULL)
//    {
//        yyerror("Memory allocation failed!");
//        exit(1);
//    }

    node = symbol;
    SYMBOL_TABLE_NODE *table;

    while (node != NULL)
    {
        table = node->symbolTable;
        //printf("SymTableNode: %s\n", table->id);
        while (table != NULL)
        {
            //printf("SymTableNode: %s\n", table->id);
            if (strcmp((symbol->data.symbol.id), (table->id)) == 0)
            {
                RET_VAL val = eval(table->value);

                if(table->type == INT_TYPE && val.type == DOUBLE_TYPE)
                {
                    warning("Precision loss on int cast from %lf to %i.", val.value, (int)trunc(val.value));
                    val.value = (int)trunc(val.value);
                    val.type = INT_TYPE;
                }
                else if(table->type == DOUBLE_TYPE || val.type == DOUBLE_TYPE)
                    val.type = DOUBLE_TYPE;

                //free node replace with a number node if it isnt one already
                if(table->value->type != NUM_NODE_TYPE)
                {
                    table->value->type = NUM_NODE_TYPE;
                    table->value->data.number = val;
                    //freeNode(table->value);
                    //table->value = createNumberNode(val.value, val.type);
                }
                return val;
            }
            //warning("symbol \"%s\" evaluating!", symbol->data.symbol.id);

            table = table->next;
        }
        /*warning("Jump to parent!");
        if(node->parent == NULL)
            warning("parent NULL!");
        //*/
        node = node->parent;
    }
    warning("Undefined Symbol \"%s\" evaluated! NAN returned!", symbol->data.symbol.id);
    return NAN_RET_VAL;
}

RET_VAL evalNeg(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("neg called with no operands! nan returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;

    if(node->next != NULL)
    {
        warning("neg called with extra (ignored) operands!");
    }
    result = eval(node);
    result.value = -result.value;
    return (result);
}

RET_VAL evalAbs(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("abs called with no operands! nan returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;

    if(node->next != NULL)
    {
        warning("abs called with extra (ignored) operands!");
    }
    result = eval(node);
    result.value = fabs(result.value);

    return (result);
}

RET_VAL evalExp(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("exp called with no operands! nan returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;

    if(node->next != NULL)
    {
        warning("exp called with extra (ignored) operands!");
    }
    result.value = exp(eval(node).value);
    result.type = DOUBLE_TYPE;
    return(result);
}

RET_VAL evalLog(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("log called with no operands! nan returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;

    if(node->next != NULL)
    {
        warning("log called with extra (ignored) operands!");
    }
    result.value = log(eval(node).value);
    result.type = DOUBLE_TYPE;
    return(result);
}

RET_VAL evalSqrt(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("sqrt called with no operands! nan returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;

    if(node->next != NULL)
    {
        warning("sqrt called with extra (ignored) operands!");
    }
    result.value = sqrt(eval(node).value);
    result.type = DOUBLE_TYPE;
    return(result);
}

RET_VAL evalExp2(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("exp2 called with no operands! nan returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;

    if(node->next != NULL)
    {
        warning("exp2 called with extra (ignored) operands!");
    }

    result = eval(node);
    //result->value = exp2(result->value);
    if(result.value < 0.0)
    {
        result.type = DOUBLE_TYPE;
        result.value = exp2(result.value);
    }
    else
        result.value = exp2(result.value);

    if(result.value == INT_TYPE)
        result.value = trunc(result.value);
    return (result);
}

RET_VAL evalCbrt(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("cbrt called with no operands! nan returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;

    if(node->next != NULL)
    {
        warning("cbrt called with extra (ignored) operands!");
    }
    result.type = DOUBLE_TYPE;
    result.value = cbrt(eval(node).value);
    return (result);
}

RET_VAL evalHypot(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("hypot called with no operands! nan returned!");
        return(NAN_RET_VAL);
    }

    RET_VAL result;

    if(node->next == NULL)
    {
        result.value = eval(node).value;
        result.type = DOUBLE_TYPE;
        return(result);
    }
    result.type = DOUBLE_TYPE;
    result.value = sqrt(pow(eval(node).value, 2) + pow(evalHypot(node->next).value, 2));
    return (result);
}

RET_VAL evalAdd(AST_NODE *node)
{
    //printf("node: %s\n", node->data.symbol.id);
    RET_VAL result;
    if(node == NULL)
    {
        warning("add called with no operands, 0 returned!");
        result.type = INT_TYPE;
        result.value = 0;
        return (result);
    }
    if(node->next == NULL)
    {
        result = eval(node);
        return (result);
    }

    result = eval(node);
    RET_VAL temp;
    temp = evalAdd(node->next);

    result.type = result.type || temp.type;
    if(result.type == NO_TYPE)
        result.type = INT_TYPE;
    result.value = result.value + temp.value;

    if(!result.type)
    {
        result.value = trunc(result.value);
    }

    return (result);
}

RET_VAL evalSub(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("sub called with no operands!");
        return NAN_RET_VAL;
    }
    else if(node->next == NULL)
    {
        warning("sub called with only one argument!");
        return NAN_RET_VAL;
    }
    else if(node->next->next != NULL)
    {
        warning("sub called with extra (ignored) operands!");
    }

    RET_VAL result;
    result = eval(node);
    RET_VAL temp;
    temp = eval(node->next);

    result.type = result.type || temp.type;
    result.value = result.value - temp.value;

    if(!result.type)
    {
        result.value = trunc(result.value);
    }

    return (result);
}

RET_VAL evalMult(AST_NODE *node)
{
    RET_VAL result;

    if(node == NULL)
    {
        warning("mult called with no operands! 1 returned!");
        result.type = INT_TYPE;
        result.value = 1;
        return (result);
    }
    else if(node->next == NULL)
    {
        result = eval(node);
        return (result);
    }

    result = eval(node);
    RET_VAL temp;
    if(node->next->type == FUNC_NODE_TYPE)
        temp = eval(node->next);
    else
        temp = evalMult(node->next);

    result.type = result.type || temp.type;
    result.value = result.value * temp.value;

    if(!result.type)
    {
        result.value = trunc(result.value);
    }

    return (result);
}

RET_VAL evalDiv(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("div called with no operands!");
        return NAN_RET_VAL;
    }
    else if(node->next == NULL)
    {
        warning("div called with only one argument!");
        return NAN_RET_VAL;
    }
    else if(node->next->next != NULL)
    {
        warning("div called with extra (ignored) operands!");
    }

    RET_VAL result;
    result = eval(node);
    RET_VAL temp;
    temp = eval(node->next);

    //result->value = result->value / temp->value;
    result.type = result.type || temp.type;

    if((result.value < temp.value) && result.type == INT_TYPE)
        result.value = 0;
    else
        result.value = result.value / temp.value;

    if(!result.type)
    {
        result.value = trunc(result.value);
    }

    return (result);
}

RET_VAL evalRemainder(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("remainder called with no operands!");
        return NAN_RET_VAL;
    }
    else if(node->next == NULL)
    {
        warning("remainder called with only one argument!");
        return NAN_RET_VAL;
    }
    else if(node->next->next != NULL)
    {
        warning("remainder called with extra (ignored) operands!");
    }

    RET_VAL result;
    result = eval(node);
    RET_VAL temp;
    temp = eval(node->next);

    result.type = result.type || temp.type;
    result.value = fmod(result.value, temp.value);
    if(!result.type)
    {
        result.value = trunc(result.value);
    }

    return (result);
}

RET_VAL evalPow(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("pow called with no operands!");
        return NAN_RET_VAL;
    }
    else if(node->next == NULL)
    {
        warning("pow called with only one argument!");
        return NAN_RET_VAL;
    }
    else if(node->next->next != NULL)
    {
        warning("pow called with extra (ignored) operands!");
    }

    RET_VAL result;
    result = eval(node);
    RET_VAL temp ;
    temp = eval(node->next);

    result.type = result.type || temp.type;
    result.value = pow(result.value, temp.value);
    if(!result.type)
    {
        result.value = trunc(result.value);
    }
    return (result);
}

RET_VAL evalMax(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("max called with no operands! nan returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;
    result = eval(node);

    if(node->next == NULL)
        return(result);

    RET_VAL temp;
    if(node->next->type == FUNC_NODE_TYPE)
        temp = eval(node->next);
    else
        temp = evalMax(node->next);

    if( (result.value) > (temp.value))
    {
        return(result);
    }
    else
    {
        return (temp);
    }
}

RET_VAL evalMin(AST_NODE *node)
{
    if(node == NULL)
    {
        warning("min called with no operands! nan returned!");
        return NAN_RET_VAL;
    }

    RET_VAL result;
    result = eval(node);

    if(node->next == NULL)
        return(result);

    RET_VAL temp;
    if(node->next->type == FUNC_NODE_TYPE)
        temp = eval(node->next);
    else
        temp = evalMin(node->next);

    if( (result.value) < (temp.value))
    {
        return(result);
    }
    else
    {
        return (temp);
    }
}

RET_VAL evalRand()
{
    RET_VAL result;
    srand( time(NULL) + rand());
    result.value = (double)(rand()) / (double)RAND_MAX;
    result.type = DOUBLE_TYPE;
    return result;
}

RET_VAL evalRead()
{
    char buff[255];
    fscanf(read_target, "%s", buff);
    printf("read :: %s\n", buff);
    switch (buff[0])
    {
        case '0'...'9':
            break;
        case '+':
        case '-':
            switch (buff[1])
            {
                case '0'...'9':
                    break;
                default:
                    warning("Invalid read entry after sign! NAN returned!");
                    return NAN_RET_VAL;
            }
            break;
        default:
            warning("Invalid read entry! NAN returned!");
            return NAN_RET_VAL;
    }

    double temp = strtod(buff, NULL);
    RET_VAL result;
    result.value = temp;
    //warning("temp %lf == trunc %lf : %i", temp, trunc(temp), temp == trunc(temp));
    if(temp != trunc(temp))
        result.type = DOUBLE_TYPE;
    else
        result.type = INT_TYPE;
    return result;
}

RET_VAL evalEqual(AST_NODE *node)
{
    RET_VAL result;
    result.type = INT_TYPE;

    if(eval(node).value == eval(node->next).value)
        result.value = 1;
    else
        result.value = 0;

    return result;
}

RET_VAL evalLess(AST_NODE *node)
{
    RET_VAL result;
    result.type = INT_TYPE;

    if(eval(node).value < eval(node->next).value)
        result.value = 1;
    else
        result.value = 0;

    return result;
}

RET_VAL evalGreater(AST_NODE *node)
{
    RET_VAL result;
    result.type = INT_TYPE;

    if(eval(node).value > eval(node->next).value)
        result.value = 1;
    else
        result.value = 0;

    return result;
}

RET_VAL evalPrint(AST_NODE *node)
{
    RET_VAL result;

    if(node == NULL)
    {
        warning("Print called with no operands!");
        return NAN_RET_VAL;
    }
    else
        result = eval(node);

    if(node->next != NULL)
        warning("print called with extra (ignored) operands!");
    //warning("Printing Node!");
    printRetVal(result);
    return result;
}

RET_VAL evalFuncNode(AST_NODE *node)
{
    if (!node)
    {
        yyerror("NULL ast node passed into evalFuncNode!");
        return NAN_RET_VAL; // unreachable but kills a clang-tidy warning
    }

    switch (node->data.function.func)
    {
        case NEG_FUNC:
            return(evalNeg(node->data.function.opList));
        case ABS_FUNC:
            return(evalAbs(node->data.function.opList));
        case ADD_FUNC:
            return(evalAdd(node->data.function.opList));
        case SUB_FUNC:
            return(evalSub(node->data.function.opList));
        case MULT_FUNC:
            return(evalMult(node->data.function.opList));
        case DIV_FUNC:
            return(evalDiv(node->data.function.opList));
        case REMAINDER_FUNC:
            return(evalRemainder(node->data.function.opList));
        case EXP_FUNC:
            return(evalExp(node->data.function.opList));
        case EXP2_FUNC:
            return(evalExp2(node->data.function.opList));
        case POW_FUNC:
            return(evalPow(node->data.function.opList));
        case LOG_FUNC:
            return(evalLog(node->data.function.opList));
        case SQRT_FUNC:
            return(evalSqrt(node->data.function.opList));
        case CBRT_FUNC:
            return(evalCbrt(node->data.function.opList));
        case HYPOT_FUNC:
            return(evalHypot(node->data.function.opList));
        case MAX_FUNC:
            return(evalMax(node->data.function.opList));
        case MIN_FUNC:
            return(evalMin(node->data.function.opList));
        case RAND_FUNC:
            return(evalRand());
        case READ_FUNC:
            return(evalRead());
        case EQUAL_FUNC:
            return(evalEqual(node->data.function.opList));
        case LESS_FUNC:
            return(evalLess(node->data.function.opList));
        case GREATER_FUNC:
            return(evalGreater(node->data.function.opList));
        case PRINT_FUNC:
            return(evalPrint(node->data.function.opList));
        default:
            break;
    }
    // TODO complete the function
    // HINT:
    // the helper functions that it calls will need to be defined above it
    // because they are not declared in the .h file (and should not be)

    return NAN_RET_VAL;
}

RET_VAL evalNumNode(AST_NODE *node)
{
    if (!node)
    {
        yyerror("NULL ast node passed into evalNumNode!");
        return NAN_RET_VAL;
    }

       return(node->data.number);
    // TODO complete the function

    return NAN_RET_VAL;
}

RET_VAL eval(AST_NODE *node)
{
    if (!node)
    {
        yyerror("NULL ast node passed into eval!");
        return NAN_RET_VAL;
    }
    if(node->type == NUM_NODE_TYPE)
    {
        return evalNumNode(node);
    }
    else if(node->type == FUNC_NODE_TYPE)
    {
        return evalFuncNode(node);
    }
    else if(node->type == SCOPE_NODE_TYPE)
    {
        return eval(node->data.scope.child);
    }
    else if(node->type == SYM_NODE_TYPE)
    {
        return evalSymbol(node);
    }
    else if(node->type == COND_NODE_TYPE)
    {
        return evalCondition(node);
    }
    // TODO complete the function

    return NAN_RET_VAL;
}

// prints the type and value of a RET_VAL
void printRetVal(RET_VAL val)
{
    switch (val.type)
    {
        case INT_TYPE:
            printf("Integer : %.lf\n", val.value);
            break;
        case DOUBLE_TYPE:
            printf("Double : %lf\n", val.value);
            break;
        default:
            printf("No Type : %lf\n", val.value);
            break;
    }
}

void freeSym(SYMBOL_TABLE_NODE *table)
{
    if(table->next)
        freeSym(table->next);

    free(table->id);
    freeNode(table->value);
    free(table);
}

void freeNode(AST_NODE *node)
{
    if (!node)
        return;

    if(node->symbolTable)
        freeSym(node->symbolTable);

    switch (node->type)
    {
        case NUM_NODE_TYPE:
            break;
        case FUNC_NODE_TYPE:
            if(node->data.function.opList != NULL)
                freeNode(node->data.function.opList);
            break;
        case SCOPE_NODE_TYPE:
            freeNode(node->data.scope.child);
            break;
        case SYM_NODE_TYPE:
            free(node->data.symbol.id);
            break;
        case COND_NODE_TYPE:
            if(node->data.cond.expr1 != NULL)
                freeNode(node->data.cond.expr1);
            if(node->data.cond.expr2 != NULL)
                freeNode(node->data.cond.expr2);
            if(node->data.cond.expr3 != NULL)
                freeNode(node->data.cond.expr3);
            break;
    }

    if (node->next != NULL)
        freeNode(node->next);

    // TODO complete the function

    // look through the AST_NODE struct, decide what
    // referenced data should have freeNode called on it
    // (hint: it might be part of an s_expr_list, with more
    // nodes following it in the list)

    // if this node is FUNC_TYPE, it might have some operands
    // to free as well (but this should probably be done in
    // a call to another function, named something like
    // freeFunctionNode)

    // and, finally,
    free(node);
}
