%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(char *);

/* Symbol Table */
#define MAX_SYMBOLS 1000
typedef struct {
    char *name;
    char *type;
    int scope;
} Symbol;

Symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;
int current_scope = 0;

/* Quadruples */
#define MAX_QUADS 1000
typedef struct {
    char *op;
    char *arg1;
    char *arg2;
    char *result;
} Quadruple;

Quadruple quads[MAX_QUADS];
int quad_count = 0;
int temp_count = 0;
int label_count = 0;

/* Switch statement tracking */
char *current_switch_end = NULL;  // Track end label for breaks

/* Function prototypes */
char* new_temp();
char* new_label();
void add_symbol(char *name, char *type);
int lookup_symbol(char *name);
void gen_quad(char *op, char *arg1, char *arg2, char *result);
void print_quads();
void print_symbol_table();

extern int line_num;
%}

%union {
    int ival;
    float fval;
    char *sval;
}

%token <sval> IDENTIFIER STRING_CONST
%token <ival> INT_CONST
%token <fval> FLOAT_CONST

%token INT FLOAT STRING
%token IF THEN ELSE WHILE FOR REPEAT UNTIL
%token FUNCTION RETURN PRINT
%token SWITCH CASE DEFAULT BREAK COLON
%token PLUS MINUS MULTIPLY DIVIDE MODULO ASSIGN
%token LT GT LE GE EQ NE
%token AND OR NOT
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA

%type <sval> expression term factor
%type <sval> type

%left OR
%left AND
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT
%nonassoc UMINUS

%%

program:
        statements                      { 
                                            printf("\n=== QUADRUPLES ===\n");
                                            print_quads();
                                            printf("\n=== SYMBOL TABLE ===\n");
                                            print_symbol_table();
                                        }
        ;

statements:
        statement
        | statements statement
        ;

statement:
        declaration SEMICOLON
        | assignment SEMICOLON
        | if_statement
        | while_statement
        | for_statement
        | repeat_statement
        | switch_statement
        | function_declaration
        | print_statement SEMICOLON
        | break_statement SEMICOLON
        | block
        | SEMICOLON
        ;

block:
        LBRACE { current_scope++; } statements RBRACE { current_scope--; }
        | LBRACE RBRACE
        ;

declaration:
        type IDENTIFIER                 {
                                            add_symbol($2, $1);
                                            free($2);
                                        }
        | type IDENTIFIER ASSIGN expression {
                                            add_symbol($2, $1);
                                            gen_quad("=", $4, "", $2);
                                            free($2);
                                            free($4);
                                        }
        ;

type:
        INT                             { $$ = strdup("rakam"); }
        | FLOAT                         { $$ = strdup("kasr"); }
        | STRING                        { $$ = strdup("kalam"); }
        ;

assignment:
        IDENTIFIER ASSIGN expression    {
                                            if (lookup_symbol($1) == -1) {
                                                char msg[100];
                                                sprintf(msg, "Variable '%s' not declared", $1);
                                                yyerror(msg);
                                            }
                                            gen_quad("=", $3, "", $1);
                                            free($1);
                                            free($3);
                                        }
        ;

if_statement:
        IF LPAREN expression RPAREN {
                                        char *label = new_label();
                                        gen_quad("IF_FALSE", $3, "", label);
                                        $<sval>$ = label;
                                        free($3);
                                    }
        statement {
                                        char *end_label = new_label();
                                        gen_quad("GOTO", "", "", end_label);
                                        gen_quad("LABEL", "", "", $<sval>5);
                                        $<sval>$ = end_label;
                                    }
        ELSE statement {
                                        gen_quad("LABEL", "", "", $<sval>7);
                                        free($<sval>5);
                                        free($<sval>7);
                                    }
        | IF LPAREN expression RPAREN {
                                        char *label = new_label();
                                        gen_quad("IF_FALSE", $3, "", label);
                                        $<sval>$ = label;
                                        free($3);
                                    }
        statement {
                                        gen_quad("LABEL", "", "", $<sval>5);
                                        free($<sval>5);
                                    }
        ;

while_statement:
        WHILE {
                char *start_label = new_label();
                gen_quad("LABEL", "", "", start_label);
                $<sval>$ = start_label;
            }
        LPAREN expression RPAREN {
                char *end_label = new_label();
                gen_quad("IF_FALSE", $4, "", end_label);
                $<sval>$ = end_label;
                free($4);
            }
        statement {
                gen_quad("GOTO", "", "", $<sval>2);
                gen_quad("LABEL", "", "", $<sval>6);
                free($<sval>2);
                free($<sval>6);
            }
        ;

for_statement:
        FOR LPAREN assignment SEMICOLON {
                char *start_label = new_label();
                gen_quad("LABEL", "", "", start_label);
                $<sval>$ = start_label;
            }
        expression SEMICOLON assignment RPAREN {
                char *end_label = new_label();
                gen_quad("IF_FALSE", $6, "", end_label);
                $<sval>$ = end_label;
                free($6);
            }
        statement {
                gen_quad("GOTO", "", "", $<sval>5);
                gen_quad("LABEL", "", "", $<sval>10);
                free($<sval>5);
                free($<sval>10);
            }
        ;

repeat_statement:
        REPEAT {
                char *start_label = new_label();
                gen_quad("LABEL", "", "", start_label);
                $<sval>$ = start_label;
            }
        statement UNTIL LPAREN expression RPAREN SEMICOLON {
                gen_quad("IF_FALSE", $6, "", $<sval>2);
                free($<sval>2);
                free($6);
            }
        ;

switch_statement:
        SWITCH LPAREN expression RPAREN {
                $<sval>$ = $3;  // Save switch expression
                current_switch_end = new_label();  // Create single end label
            }
        LBRACE case_list RBRACE {
                gen_quad("LABEL", "", "", current_switch_end);
                free($<sval>5);
                free(current_switch_end);
                current_switch_end = NULL;
            }
        ;

case_list:
        case_item
        | case_list case_item
        ;

case_item:
        CASE INT_CONST COLON {
                char buffer[20];
                sprintf(buffer, "%d", $2);
                char *temp = new_temp();
                gen_quad("==", $<sval>0, buffer, temp);
                char *next_case = new_label();
                gen_quad("IF_FALSE", temp, "", next_case);
                $<sval>$ = next_case;
                free(temp);
            }
        statements {
                gen_quad("LABEL", "", "", $<sval>4);
                free($<sval>4);
            }
        | DEFAULT COLON statements
        ;

break_statement:
        BREAK                           {
                                            if (current_switch_end != NULL) {
                                                gen_quad("GOTO", "", "", current_switch_end);
                                            }
                                        }
        ;

function_declaration:
        FUNCTION IDENTIFIER LPAREN RPAREN block {
                                                    free($2);
                                                }
        ;

print_statement:
        PRINT expression                {
                                            gen_quad("PRINT", $2, "", "");
                                            free($2);
                                        }
        ;

expression:
        expression PLUS term            {
                                            $$ = new_temp();
                                            gen_quad("+", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | expression MINUS term         {
                                            $$ = new_temp();
                                            gen_quad("-", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | expression LT term            {
                                            $$ = new_temp();
                                            gen_quad("<", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | expression GT term            {
                                            $$ = new_temp();
                                            gen_quad(">", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | expression LE term            {
                                            $$ = new_temp();
                                            gen_quad("<=", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | expression GE term            {
                                            $$ = new_temp();
                                            gen_quad(">=", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | expression EQ term            {
                                            $$ = new_temp();
                                            gen_quad("==", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | expression NE term            {
                                            $$ = new_temp();
                                            gen_quad("!=", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | expression AND term           {
                                            $$ = new_temp();
                                            gen_quad("&&", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | expression OR term            {
                                            $$ = new_temp();
                                            gen_quad("||", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | term                          { $$ = $1; }
        ;

term:
        term MULTIPLY factor            {
                                            $$ = new_temp();
                                            gen_quad("*", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | term DIVIDE factor            {
                                            $$ = new_temp();
                                            gen_quad("/", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | term MODULO factor            {
                                            $$ = new_temp();
                                            gen_quad("%", $1, $3, $$);
                                            free($1);
                                            free($3);
                                        }
        | factor                        { $$ = $1; }
        ;

factor:
        LPAREN expression RPAREN        { $$ = $2; }
        | MINUS factor %prec UMINUS     {
                                            $$ = new_temp();
                                            gen_quad("UMINUS", $2, "", $$);
                                            free($2);
                                        }
        | NOT factor                    {
                                            $$ = new_temp();
                                            gen_quad("!", $2, "", $$);
                                            free($2);
                                        }
        | IDENTIFIER                    { $$ = $1; }
        | INT_CONST                     {
                                            char buffer[20];
                                            sprintf(buffer, "%d", $1);
                                            $$ = strdup(buffer);
                                        }
        | FLOAT_CONST                   {
                                            char buffer[20];
                                            sprintf(buffer, "%f", $1);
                                            $$ = strdup(buffer);
                                        }
        | STRING_CONST                  { $$ = $1; }
        ;

%%

/* Generate new temporary variable */
char* new_temp() {
    char *temp = (char*)malloc(20);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

/* Generate new label */
char* new_label() {
    char *label = (char*)malloc(20);
    sprintf(label, "L%d", label_count++);
    return label;
}

/* Add symbol to symbol table */
void add_symbol(char *name, char *type) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0 && 
            symbol_table[i].scope == current_scope) {
            char msg[100];
            sprintf(msg, "Variable '%s' already declared in this scope", name);
            yyerror(msg);
            return;
        }
    }
    
    symbol_table[symbol_count].name = strdup(name);
    symbol_table[symbol_count].type = strdup(type);
    symbol_table[symbol_count].scope = current_scope;
    symbol_count++;
}

/* Lookup symbol in symbol table */
int lookup_symbol(char *name) {
    for (int i = symbol_count - 1; i >= 0; i--) {
        if (strcmp(symbol_table[i].name, name) == 0 && 
            symbol_table[i].scope <= current_scope) {
            return i;
        }
    }
    return -1;
}

/* Generate quadruple */
void gen_quad(char *op, char *arg1, char *arg2, char *result) {
    quads[quad_count].op = strdup(op);
    quads[quad_count].arg1 = strdup(arg1);
    quads[quad_count].arg2 = strdup(arg2);
    quads[quad_count].result = strdup(result);
    quad_count++;
}

/* Print quadruples */
void print_quads() {
    printf("%-5s %-10s %-10s %-10s %-10s\n", "Index", "Operator", "Arg1", "Arg2", "Result");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < quad_count; i++) {
        printf("%-5d %-10s %-10s %-10s %-10s\n", 
               i, quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].result);
    }
}

/* Print symbol table */
void print_symbol_table() {
    printf("%-20s %-10s %-10s\n", "Name", "Type", "Scope");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%-20s %-10s %-10d\n", 
               symbol_table[i].name, symbol_table[i].type, symbol_table[i].scope);
    }
}

void yyerror(char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_num, s);
}

int main(void) {
    printf("SimpleLang Compiler - Phase I\n");
    printf("==============================\n\n");
    yyparse();
    return 0;
}
