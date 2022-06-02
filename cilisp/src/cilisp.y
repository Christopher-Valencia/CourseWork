%{
    #include "cilisp.h"
    #define ylog(r, p) {fprintf(flex_bison_log_file, "BISON: %s ::= %s \n", #r, #p); fflush(stdout);}
    int yylex();
    void yyerror(char*, ...);
%}

%union {
    int typeval;
    char* idval;
    double dval;
    int ival;
    struct ast_node *astNode;
    struct symbol_table_node *symbolTable;
};

%token <typeval> TYPE
%token <idval> SYMBOL
%token <ival> FUNC
%token <dval> INT DOUBLE
%token QUIT EOL EOFT LPAREN RPAREN LET COND LAMBDA

%type <astNode> s_expr f_expr s_expr_section s_expr_list number
%type <symbolTable> let_section let_list let_elem arg_list

%%

program:
    s_expr EOL {
        ylog(program, s_expr EOL);
        if ($1) {
            printRetVal(eval($1));
            freeNode($1);
        }
        YYACCEPT;
    }
    | s_expr EOFT {
        ylog(program, s_expr EOFT);
        if ($1) {
            printRetVal(eval($1));
            freeNode($1);
        }
        exit(EXIT_SUCCESS);
    }
    | EOL {
        ylog(program, EOL);
        YYACCEPT;  // paranoic; main skips blank lines
    }
    | EOFT {
        ylog(program, EOFT);
        exit(EXIT_SUCCESS);
    };


s_expr:
    SYMBOL {
        ylog(s_expr, symbol);
        $$ = createSymbolNode($1);
    }
    | LPAREN let_section s_expr RPAREN {
        ylog(s_expr, LPAREN let_section s_expr RPAREN);
        $$ = createScopeNode($2, $3);
    }
    | f_expr {
        ylog(s_expr, f_expr);
        $$ = $1;
    }
    | number {
        ylog(s_expr, number);
        $$ = $1;
    }
    | LPAREN COND s_expr s_expr s_expr RPAREN {
        ylog(s_expr, LPAREN COND s_expr s_expr s_expr RPAREN);
        $$ = createConditionNode($3, $4, $5);
    }
    | QUIT {
        ylog(s_expr, QUIT);
        exit(EXIT_SUCCESS);
    }
    | error {
        ylog(s_expr, error);
        yyerror("unexpected token");
        $$ = NULL;
    };

let_section:
    LPAREN LET let_list RPAREN {
        ylog(let_section, LPAREN LET let_list RPAREN);
        $$ = $3;
    }
    | {
        ylog(let_section, empty);
        $$ = NULL;
    };

let_list:
    let_elem {
        ylog(let_list, let_elem);
        $$ = $1;
    }
    | let_elem let_list {
        ylog(let_list, let_elem let_list);
        $$ = createLetList($1, $2);
    };

let_elem:
    LPAREN SYMBOL s_expr RPAREN {
        ylog(let_elem, LPAREN SYMBOL s_expr RPAREN);
        $$ = defineSymbol($2, $3, 2);
    }
    | LPAREN TYPE SYMBOL s_expr RPAREN {
        ylog(let_elem, LPAREN TYPE SYMBOL s_expr RPAREN);
        $$ = defineSymbol($3, $4, $2);
    }
    | LPAREN SYMBOL LAMBDA LPAREN arg_list RPAREN s_expr RPAREN {
        ylog(let_elem, LPAREN SYMBOL LAMBDA LPAREN arg_list RPAREN s_expr RPAREN);

    }
    | LPAREN TYPE SYMBOL LAMBDA LPAREN arg_list RPAREN s_expr RPAREN {
        ylog(let_elem, LPAREN TYPE SYMBOL LAMBDA LPAREN arg_list RPAREN s_expr RPAREN);

    };

f_expr:
    LPAREN FUNC s_expr_section RPAREN {
        ylog(f_expr, LPAREN FUNC s_expr_section RPAREN);
        $$ = createFunctionNode($2, $3);
    }
    | LPAREN SYMBOL s_expr_section RPAREN {
        ylog(f_expr, LPAREN SYMBOL s_expr_section RPAREN);

    };

s_expr_section:
    s_expr_list {
        ylog(s_expr_section, s_expr_list);
        $$ = $1;
    }
    | {
            ylog(s_expr, empty);
            $$ = NULL;
    };

s_expr_list:
    s_expr {
        ylog(s_expr_list, s_expr);
        $$ = $1;
    }
    | s_expr s_expr_list {
        ylog(s_expr_list, s_expr s_expr_list);
        $$ = addExpressionToList($1, $2);
    };

number:
    INT {
        ylog(number, INT);
        $$ = createNumberNode($1, INT_TYPE);
    }
    | DOUBLE {
        ylog(number, DOUBLE);
        $$ = createNumberNode($1, DOUBLE_TYPE);
    };

arg_list:
    SYMBOL {
        ylog(arg_list, SYMBOL);
        $$ = $1;
    }
    | SYMBOL arg_list {
        ylog(arg_list, SYMBOL arg_list);
    };

%%