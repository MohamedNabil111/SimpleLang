%{
/**
 * SimpleLang Compiler - Phase 2
 * Lexer (Flex)
 * 
 * Arabic-style keywords for a custom programming language.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

// Column tracking for better error messages
int column = 1;
#define YY_USER_ACTION { column += yyleng; }
%}

%option noyywrap
%option yylineno

%%

    /* Keywords - Arabic transliteration */
"rakam"           { return INT; }
"kasr"            { return FLOAT; }
"kalam"           { return STRING; }
"mantiq"          { return BOOL; }
"sabit"           { return CONST; }
"law"             { return IF; }
"walla"           { return ELSE; }
"tool ma"         { return WHILE; }
"lef"             { return FOR; }
"karrar"          { return DO; }
"le7ad"           { return UNTIL; }
"shoghla"         { return FUNCTION; }
"ragga3"          { return RETURN; }
"etba3"           { return PRINT; }
"ekhtar"          { return SWITCH; }
"7ala"            { return CASE; }
"asasya"          { return DEFAULT; }
"ekhla3"          { return BREAK; }
"kamel"           { return CONTINUE; }
"sa7"             { yylval.bval = 1; return BOOL_CONST; }
"ghalat"          { yylval.bval = 0; return BOOL_CONST; }

    /* Identifiers */
[a-zA-Z_][a-zA-Z0-9_]*  {
                            yylval.sval = strdup(yytext);
                            return IDENTIFIER;
                        }

    /* Integer constants */
[0-9]+              {
                        yylval.ival = atoi(yytext);
                        return INT_CONST;
                    }

    /* Float constants */
[0-9]+"."[0-9]+     {
                        yylval.fval = atof(yytext);
                        return FLOAT_CONST;
                    }

    /* String constants */
\"([^\"\\]|\\.)*\"  {
                        // Remove quotes and handle escape sequences
                        yylval.sval = strdup(yytext);
                        return STRING_CONST;
                    }

    /* Compound assignment operators */
"+="            { return PLUS_ASSIGN; }
"-="            { return MINUS_ASSIGN; }
"*="            { return MUL_ASSIGN; }
"/="            { return DIV_ASSIGN; }
"%="            { return MOD_ASSIGN; }

    /* Increment/Decrement */
"++"            { return INCREMENT; }
"--"            { return DECREMENT; }

    /* Arithmetic operators */
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
"%"             { return MODULO; }
"^"             { return POWER; }

    /* Assignment */
"="             { return ASSIGN; }

    /* Comparison operators */
"<"             { return LT; }
">"             { return GT; }
"<="            { return LE; }
">="            { return GE; }
"=="            { return EQ; }
"!="            { return NE; }

    /* Logical operators */
"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }

    /* Bitwise operators */
"&"             { return BIT_AND; }
"|"             { return BIT_OR; }
"~"             { return BIT_NOT; }
"<<"            { return LSHIFT; }
">>"            { return RSHIFT; }

    /* Delimiters */
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
";"             { return SEMICOLON; }
","             { return COMMA; }
":"             { return COLON; }

    /* Whitespace */
[ \t]+          { /* ignore whitespace */ }

    /* Newline */
\r?\n           { column = 1; }

    /* Single-line comment */
"//".*          { /* ignore comment */ }

    /* Multi-line comment */
"/*"([^*]|\*+[^*/])*\*+"/"  { /* ignore multi-line comment */ }

    /* Unknown character */
.               { 
                    fprintf(stderr, "Lexical Error at line %d, column %d: Unknown character '%s'\n", 
                            yylineno, column, yytext);
                }

%%
