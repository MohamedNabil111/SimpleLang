%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

int line_num = 1;
void yyerror(char *);
%}

%option noyywrap

%%

    /* Keywords */
"rakam"           { return INT; }
"kasr"         { return FLOAT; }
"kalam"        { return STRING; }
"law"           { return IF; }
"yb2a"          { return THEN; }
"law la2 yb2a"  { return ELSE; }
"tool ma"       { return WHILE; }
"for"           { return FOR; }
"karrar"        { return REPEAT; }
"le7ad"         { return UNTIL; }
"function"      { return FUNCTION; }
"ragga3"        { return RETURN; }
"etba3"         { return PRINT; }
"ekhtar"        { return SWITCH; }
"7ala"          { return CASE; }
"asasya"       { return DEFAULT; }
"ekhla3"         { return BREAK; }
":"             { return COLON; }

    /* Identifiers */
[a-zA-Z_][a-zA-Z0-9_]*  {
                            yylval.sval = strdup(yytext);
                            return IDENTIFIER;
                        }

    /* Integer constants */
[0-9]+          {
                    yylval.ival = atoi(yytext);
                    return INT_CONST;
                }

    /* Float constants */
[0-9]+"."[0-9]+ {
                    yylval.fval = atof(yytext);
                    return FLOAT_CONST;
                }

    /* String constants */
\"[^\"]*\"      {
                    yylval.sval = strdup(yytext);
                    return STRING_CONST;
                }

    /* Operators */
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
"%"             { return MODULO; }
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

    /* Delimiters */
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
";"             { return SEMICOLON; }
","             { return COMMA; }

    /* Whitespace */
[ \t]+          ; /* ignore whitespace */

    /* Newline - handle both Unix (\n) and Windows (\r\n) line endings */
\r?\n           { line_num++; }

    /* Comments */
"//".*          ; /* single-line comment */

    /* Unknown character */
.               { 
                    char msg[100];
                    sprintf(msg, "Unknown character: %s at line %d", yytext, line_num);
                    yyerror(msg);
                }

%%
