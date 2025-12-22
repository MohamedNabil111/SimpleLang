%{
/**
 * SimpleLang Compiler - Phase 2
 * Parser (Bison/Yacc)
 * 
 * Features:
 * - Symbol table with scoping
 * - Quadruple generation
 * - Semantic analysis
 * - Error recovery
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "val.h"
#include "symbol_table.h"
#include "quadruples.h"
#include "semantic.h"

// External declarations
extern int yylineno;
extern char *yytext;
extern int yylex(void);
extern FILE *yyin;

// Error handling
void yyerror(const char *s);
int syntax_error_count = 0;

// Scope management
SymbolTable *current_scope = NULL;
SymbolTable *global_scope = NULL;

// Function tracking
Symbol *current_function = NULL;
Parameter *current_params = NULL;

// Loop/switch tracking for break/continue
#define MAX_NESTED_LOOPS 32
char *break_label_stack[MAX_NESTED_LOOPS];
char *continue_label_stack[MAX_NESTED_LOOPS];
int loop_stack_top = -1;

// Switch tracking
char *current_switch_end = NULL;
char *current_switch_place = NULL;
Type current_switch_type;

// Helper functions
val* create_int_val(int i);
val* create_float_val(float f);
val* create_string_val(const char *s);
val* create_bool_val(int b);
val* perform_arithmetic(val *v1, const char *op, val *v2);
val* perform_comparison(val *v1, const char *op, val *v2);
val* perform_logical(val *v1, const char *op, val *v2);
void push_loop(char *break_lbl, char *continue_lbl);
void pop_loop(void);
%}

%code requires {
    #include "val.h"
    #include "symbol_table.h"
    #include "parameter.h"
}

/* Enable verbose error messages */
%define parse.error verbose

/* Value types */
%union {
    int ival;
    float fval;
    char *sval;
    int bval;
    val *vval;
    Parameter *pval;
    Type tval;
}

/* Token declarations */
%token <sval> IDENTIFIER STRING_CONST
%token <ival> INT_CONST
%token <fval> FLOAT_CONST
%token <bval> BOOL_CONST

/* Type keywords */
%token INT FLOAT STRING BOOL CONST

/* Control flow */
%token IF ELSE WHILE FOR DO UNTIL
%token SWITCH CASE DEFAULT
%token BREAK CONTINUE RETURN

/* Other keywords */
%token FUNCTION PRINT

/* Operators */
%token PLUS MINUS MULTIPLY DIVIDE MODULO POWER
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token INCREMENT DECREMENT
%token LT GT LE GE EQ NE
%token AND OR NOT
%token BIT_AND BIT_OR BIT_NOT LSHIFT RSHIFT

/* Delimiters */
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token SEMICOLON COMMA COLON

/* Type declarations for non-terminals */
%type <vval> expression logical_or_expr logical_and_expr
%type <vval> equality_expr relational_expr additive_expr
%type <vval> multiplicative_expr unary_expr primary_expr
%type <vval> function_call
%type <tval> type_specifier
%type <pval> parameter_list parameter_declaration argument_list

/* Operator precedence (lowest to highest) */
%left OR
%left AND
%left BIT_OR
%left BIT_AND
%left EQ NE
%left LT GT LE GE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right POWER
%right NOT BIT_NOT
%right INCREMENT DECREMENT
%nonassoc UMINUS

/* Dangling else resolution */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

/*=============================================================================
 * PROGRAM STRUCTURE
 *=============================================================================*/

program:
    { 
        // Initialize global scope
        global_scope = create_symbol_table(NULL);
        current_scope = global_scope;
    }
    declarations
    {
        // Print results
        printf("\n");
        print_quads();
        
        // Output symbol table to file
        SYMTAB_FILE = fopen("symbols.txt", "w");
        if (SYMTAB_FILE) {
            print_symbol_table(current_scope);
            fclose(SYMTAB_FILE);
        }
        
        printf("\n=== SYMBOL TABLE ===\n");
        print_symbol_table_stdout(current_scope);
        
        // Cleanup
        free_symbol_table(global_scope);
        
        // Summary
        printf("\n=== COMPILATION SUMMARY ===\n");
        printf("Syntax errors: %d\n", syntax_error_count);
        printf("Semantic errors: %d\n", semantic_error_count);
        printf("Warnings: %d\n", semantic_warning_count);
        
        if (syntax_error_count == 0 && semantic_error_count == 0) {
            printf("Compilation successful!\n");
        } else {
            printf("Compilation failed.\n");
        }
    }
    ;

declarations:
    /* empty */
    | declarations declaration
    | declarations function_definition
    | declarations statement
    ;

/*=============================================================================
 * DECLARATIONS
 *=============================================================================*/

declaration:
    type_specifier IDENTIFIER SEMICOLON
    {
        val *v = create_val($1);
        v->place = strdup($2);
        Symbol *sym = insert_symbol(current_scope, $2, v, SYM_VARIABLE, 0, NULL, yylineno);
        if (sym) {
            add_quad("DECL", type_to_string($1), "", $2);
        }
        free($2);
    }
    | type_specifier IDENTIFIER ASSIGN expression SEMICOLON
    {
        // Check type compatibility
        if (!check_assignment_type($1, $4->type)) {
            semantic_error(yylineno, "Type mismatch in initialization: cannot assign %s to %s",
                          type_to_string($4->type), type_to_string($1));
        }
        
        val *v = create_val($1);
        v->place = strdup($2);
        
        // Copy value
        switch ($1) {
            case TYPE_INT:
                v->data.i = ($4->type == TYPE_FLOAT) ? (int)$4->data.f : $4->data.i;
                break;
            case TYPE_FLOAT:
                v->data.f = ($4->type == TYPE_INT) ? (float)$4->data.i : $4->data.f;
                break;
            case TYPE_STRING:
                if ($4->data.s) v->data.s = strdup($4->data.s);
                break;
            case TYPE_BOOL:
                v->data.b = $4->data.b;
                break;
            default:
                break;
        }
        
        Symbol *sym = insert_symbol(current_scope, $2, v, SYM_VARIABLE, 0, NULL, yylineno);
        if (sym) {
            sym->is_initialized = true;
            add_quad("DECL", type_to_string($1), "", $2);
            add_quad("ASSIGN", $4->place, "", $2);
        }
        
        free($2);
        free_val($4);
    }
    | CONST type_specifier IDENTIFIER ASSIGN expression SEMICOLON
    {
        // Constants must be initialized
        if (!check_assignment_type($2, $5->type)) {
            semantic_error(yylineno, "Type mismatch in constant initialization");
        }
        
        val *v = create_val($2);
        v->place = strdup($3);
        v->is_constant = true;
        
        switch ($2) {
            case TYPE_INT:
                v->data.i = ($5->type == TYPE_FLOAT) ? (int)$5->data.f : $5->data.i;
                break;
            case TYPE_FLOAT:
                v->data.f = ($5->type == TYPE_INT) ? (float)$5->data.i : $5->data.f;
                break;
            case TYPE_STRING:
                if ($5->data.s) v->data.s = strdup($5->data.s);
                break;
            case TYPE_BOOL:
                v->data.b = $5->data.b;
                break;
            default:
                break;
        }
        
        Symbol *sym = insert_symbol(current_scope, $3, v, SYM_CONSTANT, 0, NULL, yylineno);
        if (sym) {
            sym->is_initialized = true;
            add_quad("CONST", type_to_string($2), $5->place, $3);
        }
        
        free($3);
        free_val($5);
    }
    ;

type_specifier:
    INT     { $$ = TYPE_INT; }
    | FLOAT { $$ = TYPE_FLOAT; }
    | STRING { $$ = TYPE_STRING; }
    | BOOL  { $$ = TYPE_BOOL; }
    ;

/*=============================================================================
 * FUNCTIONS
 *=============================================================================*/

function_definition:
    type_specifier IDENTIFIER LPAREN parameter_list RPAREN
    {
        // Create function value
        val *func_val = create_val($1);
        func_val->place = strdup($2);
        func_val->endLabel = new_label();
        
        int param_count = count_params($4);
        Symbol *func = insert_symbol(current_scope, $2, func_val, SYM_FUNCTION, 
                                     param_count, $4, yylineno);
        current_function = func;
        current_params = $4;
        
        add_quad("FUNC", $2, "", "");
    }
    block
    {
        add_quad("ENDFUNC", $<sval>2, "", "");
        current_function = NULL;
        current_params = NULL;
    }
    | type_specifier IDENTIFIER LPAREN RPAREN
    {
        val *func_val = create_val($1);
        func_val->place = strdup($2);
        func_val->endLabel = new_label();
        
        Symbol *func = insert_symbol(current_scope, $2, func_val, SYM_FUNCTION, 0, NULL, yylineno);
        current_function = func;
        
        add_quad("FUNC", $2, "", "");
    }
    block
    {
        add_quad("ENDFUNC", $<sval>2, "", "");
        current_function = NULL;
    }
    ;

parameter_list:
    parameter_declaration
    { $$ = $1; }
    | parameter_list COMMA parameter_declaration
    { $$ = append_param($1, $3); }
    ;

parameter_declaration:
    type_specifier IDENTIFIER
    {
        val *v = create_val($1);
        v->place = strdup($2);
        $$ = create_param($2, v);
        free($2);
    }
    ;

/*=============================================================================
 * STATEMENTS
 *=============================================================================*/

statement:
    expression_statement
    | declaration
    | block
    | if_statement
    | while_statement
    | do_while_statement
    | for_statement
    | switch_statement
    | break_statement
    | continue_statement
    | return_statement
    | print_statement
    | error SEMICOLON
    {
        fprintf(stderr, "Syntax error recovered at line %d\n", yylineno);
        syntax_error_count++;
        yyerrok;
    }
    | error RBRACE
    {
        fprintf(stderr, "Syntax error recovered at block end, line %d\n", yylineno);
        syntax_error_count++;
        yyerrok;
    }
    ;

expression_statement:
    SEMICOLON
    | expression SEMICOLON { free_val($1); }
    | assignment_statement SEMICOLON
    ;

assignment_statement:
    IDENTIFIER ASSIGN expression
    {
        Symbol *sym = lookup_symbol(current_scope, $1);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $1);
        } else {
            sym->is_used = true;
            
            if (sym->sym_type == SYM_CONSTANT) {
                semantic_error(yylineno, "Cannot assign to constant '%s'", $1);
            } else {
                if (!check_assignment_type(sym->value->type, $3->type)) {
                    semantic_error(yylineno, "Type mismatch in assignment to '%s'", $1);
                }
                sym->is_initialized = true;
                add_quad("ASSIGN", $3->place, "", $1);
            }
        }
        free($1);
        free_val($3);
    }
    | IDENTIFIER PLUS_ASSIGN expression
    {
        Symbol *sym = lookup_symbol(current_scope, $1);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $1);
        } else if (sym->sym_type == SYM_CONSTANT) {
            semantic_error(yylineno, "Cannot modify constant '%s'", $1);
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("ADD", $1, $3->place, temp);
            add_quad("ASSIGN", temp, "", $1);
            free(temp);
        }
        free($1);
        free_val($3);
    }
    | IDENTIFIER MINUS_ASSIGN expression
    {
        Symbol *sym = lookup_symbol(current_scope, $1);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $1);
        } else if (sym->sym_type == SYM_CONSTANT) {
            semantic_error(yylineno, "Cannot modify constant '%s'", $1);
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("SUB", $1, $3->place, temp);
            add_quad("ASSIGN", temp, "", $1);
            free(temp);
        }
        free($1);
        free_val($3);
    }
    | IDENTIFIER MUL_ASSIGN expression
    {
        Symbol *sym = lookup_symbol(current_scope, $1);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $1);
        } else if (sym->sym_type == SYM_CONSTANT) {
            semantic_error(yylineno, "Cannot modify constant '%s'", $1);
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("MUL", $1, $3->place, temp);
            add_quad("ASSIGN", temp, "", $1);
            free(temp);
        }
        free($1);
        free_val($3);
    }
    | IDENTIFIER DIV_ASSIGN expression
    {
        Symbol *sym = lookup_symbol(current_scope, $1);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $1);
        } else if (sym->sym_type == SYM_CONSTANT) {
            semantic_error(yylineno, "Cannot modify constant '%s'", $1);
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("DIV", $1, $3->place, temp);
            add_quad("ASSIGN", temp, "", $1);
            free(temp);
        }
        free($1);
        free_val($3);
    }
    ;

block:
    LBRACE
    {
        // Create new scope
        SymbolTable *new_scope = create_symbol_table(current_scope);
        current_scope = new_scope;
        
        // Add function parameters to new scope
        if (current_params) {
            Parameter *p = current_params;
            while (p) {
                val *v = copy_val(p->value);
                insert_symbol(current_scope, p->name, v, SYM_VARIABLE, 0, NULL, yylineno);
                add_quad("PARAM", p->name, "", "");
                p = p->next;
            }
            current_params = NULL;  // Only add once
        }
    }
    statement_list RBRACE
    {
        // Print and cleanup scope
        SYMTAB_FILE = fopen("symbols.txt", "a");
        if (SYMTAB_FILE) {
            print_symbol_table(current_scope);
            fclose(SYMTAB_FILE);
        }
        
        SymbolTable *old_scope = current_scope;
        current_scope = old_scope->parent;
        free_symbol_table(old_scope);
    }
    ;

statement_list:
    /* empty */
    | statement_list statement
    ;

/*=============================================================================
 * CONTROL FLOW
 *=============================================================================*/

if_statement:
    IF LPAREN expression RPAREN
    {
        if ($3->type != TYPE_BOOL) {
            semantic_warning(yylineno, "Condition should be boolean type");
        }
        $3->falseLabel = new_label();
        add_quad("JMP_FALSE", $3->place, "", $3->falseLabel);
    }
    statement %prec LOWER_THAN_ELSE
    {
        add_quad("LABEL", $3->falseLabel, "", "");
        free_val($3);
    }
    | IF LPAREN expression RPAREN
    {
        if ($3->type != TYPE_BOOL) {
            semantic_warning(yylineno, "Condition should be boolean type");
        }
        $3->falseLabel = new_label();
        $3->endLabel = new_label();
        add_quad("JMP_FALSE", $3->place, "", $3->falseLabel);
    }
    statement ELSE
    {
        add_quad("JMP", "", "", $3->endLabel);
        add_quad("LABEL", $3->falseLabel, "", "");
    }
    statement
    {
        add_quad("LABEL", $3->endLabel, "", "");
        free_val($3);
    }
    ;

while_statement:
    WHILE
    {
        char *start_label = new_label();
        char *end_label = new_label();
        push_loop(end_label, start_label);
        add_quad("LABEL", start_label, "", "");
        $<sval>$ = start_label;
    }
    LPAREN expression RPAREN
    {
        if ($4->type != TYPE_BOOL) {
            semantic_warning(yylineno, "While condition should be boolean type");
        }
        add_quad("JMP_FALSE", $4->place, "", break_label_stack[loop_stack_top]);
        $<vval>$ = $4;
    }
    statement
    {
        add_quad("JMP", "", "", $<sval>2);
        add_quad("LABEL", break_label_stack[loop_stack_top], "", "");
        pop_loop();
        free_val($<vval>6);
    }
    ;

do_while_statement:
    DO
    {
        char *start_label = new_label();
        char *end_label = new_label();
        push_loop(end_label, start_label);
        add_quad("LABEL", start_label, "", "");
        $<sval>$ = start_label;
    }
    statement WHILE LPAREN expression RPAREN SEMICOLON
    {
        if ($6->type != TYPE_BOOL) {
            semantic_warning(yylineno, "Do-while condition should be boolean type");
        }
        add_quad("JMP_TRUE", $6->place, "", $<sval>2);
        add_quad("LABEL", break_label_stack[loop_stack_top], "", "");
        pop_loop();
        free_val($6);
    }
    ;

for_statement:
    FOR LPAREN for_init SEMICOLON
    {
        char *start_label = new_label();
        char *end_label = new_label();
        push_loop(end_label, start_label);
        add_quad("LABEL", start_label, "", "");
        $<sval>$ = start_label;
    }
    for_condition SEMICOLON
    {
        add_quad("JMP_FALSE", $6 ? $<vval>6->place : "1", "", break_label_stack[loop_stack_top]);
        $<sval>$ = new_label();  // update label
        add_quad("JMP", "", "", $<sval>$);  // skip update on first iteration
        $<sval>5 = new_label();  // update section label
        add_quad("LABEL", $<sval>5, "", "");
    }
    for_update RPAREN
    {
        add_quad("JMP", "", "", $<sval>5);  // go back to condition
        add_quad("LABEL", $<sval>8, "", "");  // body starts here
    }
    statement
    {
        add_quad("JMP", "", "", $<sval>5);  // go to update
        add_quad("LABEL", break_label_stack[loop_stack_top], "", "");
        pop_loop();
    }
    ;

for_init:
    /* empty */
    | assignment_statement
    | type_specifier IDENTIFIER ASSIGN expression
    {
        val *v = create_val($1);
        v->place = strdup($2);
        Symbol *sym = insert_symbol(current_scope, $2, v, SYM_VARIABLE, 0, NULL, yylineno);
        if (sym) {
            sym->is_initialized = true;
            add_quad("ASSIGN", $4->place, "", $2);
        }
        free($2);
        free_val($4);
    }
    ;

for_condition:
    /* empty */ { $<vval>$ = NULL; }
    | expression { $<vval>$ = $1; }
    ;

for_update:
    /* empty */
    | assignment_statement
    | IDENTIFIER INCREMENT
    {
        Symbol *sym = lookup_symbol(current_scope, $1);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $1);
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("ADD", $1, "1", temp);
            add_quad("ASSIGN", temp, "", $1);
            free(temp);
        }
        free($1);
    }
    | IDENTIFIER DECREMENT
    {
        Symbol *sym = lookup_symbol(current_scope, $1);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $1);
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("SUB", $1, "1", temp);
            add_quad("ASSIGN", temp, "", $1);
            free(temp);
        }
        free($1);
    }
    ;

switch_statement:
    SWITCH LPAREN expression RPAREN
    {
        current_switch_place = $3->place;
        current_switch_type = $3->type;
        current_switch_end = new_label();
        push_loop(current_switch_end, NULL);  // For break statements
    }
    LBRACE case_list RBRACE
    {
        add_quad("LABEL", current_switch_end, "", "");
        pop_loop();
        free_val($3);
        current_switch_place = NULL;
        current_switch_end = NULL;
    }
    ;

case_list:
    /* empty */
    | case_list case_item
    ;

case_item:
    CASE INT_CONST COLON
    {
        char buffer[32];
        sprintf(buffer, "%d", $2);
        char *temp = new_temp();
        add_quad("EQ", current_switch_place, buffer, temp);
        char *next_case = new_label();
        add_quad("JMP_FALSE", temp, "", next_case);
        $<sval>$ = next_case;
        free(temp);
    }
    statement_list
    {
        add_quad("LABEL", $<sval>4, "", "");
    }
    | CASE STRING_CONST COLON
    {
        char *temp = new_temp();
        add_quad("EQ", current_switch_place, $2, temp);
        char *next_case = new_label();
        add_quad("JMP_FALSE", temp, "", next_case);
        $<sval>$ = next_case;
        free(temp);
        free($2);
    }
    statement_list
    {
        add_quad("LABEL", $<sval>4, "", "");
    }
    | DEFAULT COLON statement_list
    ;

break_statement:
    BREAK SEMICOLON
    {
        if (loop_stack_top < 0) {
            semantic_error(yylineno, "'break' statement not within loop or switch");
        } else {
            add_quad("JMP", "", "", break_label_stack[loop_stack_top]);
        }
    }
    ;

continue_statement:
    CONTINUE SEMICOLON
    {
        if (loop_stack_top < 0 || continue_label_stack[loop_stack_top] == NULL) {
            semantic_error(yylineno, "'continue' statement not within loop");
        } else {
            add_quad("JMP", "", "", continue_label_stack[loop_stack_top]);
        }
    }
    ;

return_statement:
    RETURN SEMICOLON
    {
        if (current_function == NULL) {
            semantic_error(yylineno, "'return' statement outside function");
        } else if (current_function->value->type != TYPE_VOID) {
            semantic_warning(yylineno, "Non-void function should return a value");
        }
        add_quad("RETURN", "", "", "");
    }
    | RETURN expression SEMICOLON
    {
        if (current_function == NULL) {
            semantic_error(yylineno, "'return' statement outside function");
        } else {
            if (!check_assignment_type(current_function->value->type, $2->type)) {
                semantic_error(yylineno, "Return type mismatch");
            }
            add_quad("RETURN", $2->place, "", "");
        }
        free_val($2);
    }
    ;

print_statement:
    PRINT expression SEMICOLON
    {
        add_quad("PRINT", $2->place, "", "");
        free_val($2);
    }
    | PRINT LPAREN expression RPAREN SEMICOLON
    {
        add_quad("PRINT", $3->place, "", "");
        free_val($3);
    }
    ;

/*=============================================================================
 * EXPRESSIONS
 *=============================================================================*/

expression:
    logical_or_expr { $$ = $1; }
    ;

logical_or_expr:
    logical_and_expr { $$ = $1; }
    | logical_or_expr OR logical_and_expr
    {
        $$ = perform_logical($1, "||", $3);
        free_val($1);
        free_val($3);
    }
    ;

logical_and_expr:
    equality_expr { $$ = $1; }
    | logical_and_expr AND equality_expr
    {
        $$ = perform_logical($1, "&&", $3);
        free_val($1);
        free_val($3);
    }
    ;

equality_expr:
    relational_expr { $$ = $1; }
    | equality_expr EQ relational_expr
    {
        $$ = perform_comparison($1, "==", $3);
        free_val($1);
        free_val($3);
    }
    | equality_expr NE relational_expr
    {
        $$ = perform_comparison($1, "!=", $3);
        free_val($1);
        free_val($3);
    }
    ;

relational_expr:
    additive_expr { $$ = $1; }
    | relational_expr LT additive_expr
    {
        $$ = perform_comparison($1, "<", $3);
        free_val($1);
        free_val($3);
    }
    | relational_expr GT additive_expr
    {
        $$ = perform_comparison($1, ">", $3);
        free_val($1);
        free_val($3);
    }
    | relational_expr LE additive_expr
    {
        $$ = perform_comparison($1, "<=", $3);
        free_val($1);
        free_val($3);
    }
    | relational_expr GE additive_expr
    {
        $$ = perform_comparison($1, ">=", $3);
        free_val($1);
        free_val($3);
    }
    ;

additive_expr:
    multiplicative_expr { $$ = $1; }
    | additive_expr PLUS multiplicative_expr
    {
        $$ = perform_arithmetic($1, "+", $3);
        free_val($1);
        free_val($3);
    }
    | additive_expr MINUS multiplicative_expr
    {
        $$ = perform_arithmetic($1, "-", $3);
        free_val($1);
        free_val($3);
    }
    ;

multiplicative_expr:
    unary_expr { $$ = $1; }
    | multiplicative_expr MULTIPLY unary_expr
    {
        $$ = perform_arithmetic($1, "*", $3);
        free_val($1);
        free_val($3);
    }
    | multiplicative_expr DIVIDE unary_expr
    {
        $$ = perform_arithmetic($1, "/", $3);
        free_val($1);
        free_val($3);
    }
    | multiplicative_expr MODULO unary_expr
    {
        $$ = perform_arithmetic($1, "%", $3);
        free_val($1);
        free_val($3);
    }
    ;

unary_expr:
    primary_expr { $$ = $1; }
    | MINUS unary_expr %prec UMINUS
    {
        $$ = create_val($2->type);
        $$->place = new_temp();
        add_quad("NEG", $2->place, "", $$->place);
        
        if ($2->type == TYPE_INT) {
            $$->data.i = -$2->data.i;
        } else if ($2->type == TYPE_FLOAT) {
            $$->data.f = -$2->data.f;
        }
        free_val($2);
    }
    | NOT unary_expr
    {
        $$ = create_val(TYPE_BOOL);
        $$->place = new_temp();
        add_quad("NOT", $2->place, "", $$->place);
        $$->data.b = !$2->data.b;
        free_val($2);
    }
    | INCREMENT IDENTIFIER
    {
        Symbol *sym = lookup_symbol(current_scope, $2);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $2);
            $$ = create_val(TYPE_INT);
        } else {
            sym->is_used = true;
            $$ = copy_val(sym->value);
            char *temp = new_temp();
            add_quad("ADD", $2, "1", temp);
            add_quad("ASSIGN", temp, "", $2);
            $$->place = temp;
        }
        free($2);
    }
    | DECREMENT IDENTIFIER
    {
        Symbol *sym = lookup_symbol(current_scope, $2);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $2);
            $$ = create_val(TYPE_INT);
        } else {
            sym->is_used = true;
            $$ = copy_val(sym->value);
            char *temp = new_temp();
            add_quad("SUB", $2, "1", temp);
            add_quad("ASSIGN", temp, "", $2);
            $$->place = temp;
        }
        free($2);
    }
    ;

primary_expr:
    LPAREN expression RPAREN { $$ = $2; }
    | IDENTIFIER
    {
        Symbol *sym = lookup_symbol(current_scope, $1);
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", $1);
            $$ = create_val(TYPE_INT);
            $$->place = strdup($1);
        } else {
            sym->is_used = true;
            if (!sym->is_initialized && sym->sym_type == SYM_VARIABLE) {
                semantic_warning(yylineno, "Variable '%s' may be used uninitialized", $1);
            }
            $$ = copy_val(sym->value);
            $$->place = strdup($1);
        }
        free($1);
    }
    | INT_CONST
    {
        $$ = create_int_val($1);
    }
    | FLOAT_CONST
    {
        $$ = create_float_val($1);
    }
    | STRING_CONST
    {
        $$ = create_string_val($1);
        free($1);
    }
    | BOOL_CONST
    {
        $$ = create_bool_val($1);
    }
    | function_call { $$ = $1; }
    ;

function_call:
    IDENTIFIER LPAREN argument_list RPAREN
    {
        Symbol *func = lookup_symbol(current_scope, $1);
        if (!func) {
            semantic_error(yylineno, "Undefined function '%s'", $1);
            $$ = create_val(TYPE_INT);
        } else if (func->sym_type != SYM_FUNCTION) {
            semantic_error(yylineno, "'%s' is not a function", $1);
            $$ = create_val(TYPE_INT);
        } else {
            func->is_used = true;
            
            // Validate arguments
            int arg_count = count_params($3);
            if (arg_count != func->param_count) {
                semantic_error(yylineno, "Function '%s' expects %d arguments, got %d",
                              $1, func->param_count, arg_count);
            }
            
            // Generate parameter passing quads
            Parameter *arg = $3;
            while (arg) {
                add_quad("ARG", arg->value->place, "", "");
                arg = arg->next;
            }
            
            $$ = create_val(func->value->type);
            $$->place = new_temp();
            add_quad("CALL", $1, "", $$->place);
        }
        free($1);
        free_params($3);
    }
    | IDENTIFIER LPAREN RPAREN
    {
        Symbol *func = lookup_symbol(current_scope, $1);
        if (!func) {
            semantic_error(yylineno, "Undefined function '%s'", $1);
            $$ = create_val(TYPE_INT);
        } else if (func->sym_type != SYM_FUNCTION) {
            semantic_error(yylineno, "'%s' is not a function", $1);
            $$ = create_val(TYPE_INT);
        } else {
            func->is_used = true;
            
            if (func->param_count != 0) {
                semantic_error(yylineno, "Function '%s' expects %d arguments, got 0",
                              $1, func->param_count);
            }
            
            $$ = create_val(func->value->type);
            $$->place = new_temp();
            add_quad("CALL", $1, "", $$->place);
        }
        free($1);
    }
    ;

argument_list:
    expression
    {
        Parameter *p = (Parameter*)malloc(sizeof(Parameter));
        p->name = new_temp();
        p->value = $1;
        p->next = NULL;
        $$ = p;
    }
    | argument_list COMMA expression
    {
        Parameter *p = (Parameter*)malloc(sizeof(Parameter));
        p->name = new_temp();
        p->value = $3;
        p->next = NULL;
        $$ = append_param($1, p);
    }
    ;

%%

/*=============================================================================
 * HELPER FUNCTIONS
 *=============================================================================*/

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
    syntax_error_count++;
}

val* create_int_val(int i) {
    val *v = create_val(TYPE_INT);
    v->data.i = i;
    v->place = (char*)malloc(32);
    sprintf(v->place, "%d", i);
    v->is_constant = true;
    return v;
}

val* create_float_val(float f) {
    val *v = create_val(TYPE_FLOAT);
    v->data.f = f;
    v->place = (char*)malloc(32);
    sprintf(v->place, "%.6f", f);
    v->is_constant = true;
    return v;
}

val* create_string_val(const char *s) {
    val *v = create_val(TYPE_STRING);
    v->data.s = strdup(s);
    v->place = strdup(s);
    v->is_constant = true;
    return v;
}

val* create_bool_val(int b) {
    val *v = create_val(TYPE_BOOL);
    v->data.b = b;
    v->place = (char*)malloc(8);
    sprintf(v->place, "%s", b ? "true" : "false");
    v->is_constant = true;
    return v;
}

val* perform_arithmetic(val *v1, const char *op, val *v2) {
    Type result_type;
    if (!check_arithmetic_types(v1->type, v2->type, &result_type)) {
        semantic_error(yylineno, "Invalid operand types for '%s' operator", op);
        return create_val(TYPE_INT);
    }
    
    val *result = create_val(result_type);
    result->place = new_temp();
    
    const char *quad_op;
    if (strcmp(op, "+") == 0) quad_op = "ADD";
    else if (strcmp(op, "-") == 0) quad_op = "SUB";
    else if (strcmp(op, "*") == 0) quad_op = "MUL";
    else if (strcmp(op, "/") == 0) quad_op = "DIV";
    else if (strcmp(op, "%") == 0) quad_op = "MOD";
    else quad_op = op;
    
    add_quad(quad_op, v1->place, v2->place, result->place);
    
    // Compute value for constant folding
    if (result_type == TYPE_FLOAT) {
        float a = (v1->type == TYPE_INT) ? (float)v1->data.i : v1->data.f;
        float b = (v2->type == TYPE_INT) ? (float)v2->data.i : v2->data.f;
        
        if (strcmp(op, "+") == 0) result->data.f = a + b;
        else if (strcmp(op, "-") == 0) result->data.f = a - b;
        else if (strcmp(op, "*") == 0) result->data.f = a * b;
        else if (strcmp(op, "/") == 0) result->data.f = (b != 0) ? a / b : 0;
    } else {
        int a = (v1->type == TYPE_FLOAT) ? (int)v1->data.f : v1->data.i;
        int b = (v2->type == TYPE_FLOAT) ? (int)v2->data.f : v2->data.i;
        
        if (strcmp(op, "+") == 0) result->data.i = a + b;
        else if (strcmp(op, "-") == 0) result->data.i = a - b;
        else if (strcmp(op, "*") == 0) result->data.i = a * b;
        else if (strcmp(op, "/") == 0) result->data.i = (b != 0) ? a / b : 0;
        else if (strcmp(op, "%") == 0) result->data.i = (b != 0) ? a % b : 0;
    }
    
    return result;
}

val* perform_comparison(val *v1, const char *op, val *v2) {
    if (!check_comparison_types(v1->type, v2->type)) {
        semantic_error(yylineno, "Invalid operand types for '%s' operator", op);
    }
    
    val *result = create_val(TYPE_BOOL);
    result->place = new_temp();
    
    const char *quad_op = op;
    add_quad(quad_op, v1->place, v2->place, result->place);
    
    // Compute value
    float a = (v1->type == TYPE_FLOAT) ? v1->data.f : (float)v1->data.i;
    float b = (v2->type == TYPE_FLOAT) ? v2->data.f : (float)v2->data.i;
    
    if (strcmp(op, "==") == 0) result->data.b = (a == b);
    else if (strcmp(op, "!=") == 0) result->data.b = (a != b);
    else if (strcmp(op, "<") == 0) result->data.b = (a < b);
    else if (strcmp(op, ">") == 0) result->data.b = (a > b);
    else if (strcmp(op, "<=") == 0) result->data.b = (a <= b);
    else if (strcmp(op, ">=") == 0) result->data.b = (a >= b);
    
    return result;
}

val* perform_logical(val *v1, const char *op, val *v2) {
    val *result = create_val(TYPE_BOOL);
    result->place = new_temp();
    
    add_quad(op, v1->place, v2->place, result->place);
    
    int a = v1->data.b;
    int b = v2->data.b;
    
    if (strcmp(op, "&&") == 0) result->data.b = a && b;
    else if (strcmp(op, "||") == 0) result->data.b = a || b;
    
    return result;
}

void push_loop(char *break_lbl, char *continue_lbl) {
    if (loop_stack_top < MAX_NESTED_LOOPS - 1) {
        loop_stack_top++;
        break_label_stack[loop_stack_top] = break_lbl;
        continue_label_stack[loop_stack_top] = continue_lbl;
    } else {
        semantic_error(yylineno, "Too many nested loops");
    }
}

void pop_loop(void) {
    if (loop_stack_top >= 0) {
        break_label_stack[loop_stack_top] = NULL;
        continue_label_stack[loop_stack_top] = NULL;
        loop_stack_top--;
    }
}

int main(int argc, char **argv) {
    printf("===========================================\n");
    printf("   SimpleLang Compiler - Phase 2\n");
    printf("===========================================\n\n");
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Error opening file");
            return 1;
        }
        printf("Compiling: %s\n\n", argv[1]);
    } else {
        printf("Reading from stdin...\n\n");
        yyin = stdin;
    }
    
    // Clear output file
    FILE *f = fopen("symbols.txt", "w");
    if (f) fclose(f);
    
    yyparse();
    
    if (argc > 1 && yyin != stdin) {
        fclose(yyin);
    }
    
    return (syntax_error_count > 0 || semantic_error_count > 0) ? 1 : 0;
}
