/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 62 "simplelang.y"

    #include "val.h"
    #include "symbol_table.h"
    #include "parameter.h"

#line 55 "y.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING_CONST = 259,            /* STRING_CONST  */
    INT_CONST = 260,               /* INT_CONST  */
    FLOAT_CONST = 261,             /* FLOAT_CONST  */
    BOOL_CONST = 262,              /* BOOL_CONST  */
    INT = 263,                     /* INT  */
    FLOAT = 264,                   /* FLOAT  */
    STRING = 265,                  /* STRING  */
    BOOL = 266,                    /* BOOL  */
    CONST = 267,                   /* CONST  */
    IF = 268,                      /* IF  */
    ELSE = 269,                    /* ELSE  */
    WHILE = 270,                   /* WHILE  */
    FOR = 271,                     /* FOR  */
    DO = 272,                      /* DO  */
    UNTIL = 273,                   /* UNTIL  */
    SWITCH = 274,                  /* SWITCH  */
    CASE = 275,                    /* CASE  */
    DEFAULT = 276,                 /* DEFAULT  */
    BREAK = 277,                   /* BREAK  */
    CONTINUE = 278,                /* CONTINUE  */
    RETURN = 279,                  /* RETURN  */
    FUNCTION = 280,                /* FUNCTION  */
    PRINT = 281,                   /* PRINT  */
    PLUS = 282,                    /* PLUS  */
    MINUS = 283,                   /* MINUS  */
    MULTIPLY = 284,                /* MULTIPLY  */
    DIVIDE = 285,                  /* DIVIDE  */
    MODULO = 286,                  /* MODULO  */
    POWER = 287,                   /* POWER  */
    ASSIGN = 288,                  /* ASSIGN  */
    PLUS_ASSIGN = 289,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 290,            /* MINUS_ASSIGN  */
    MUL_ASSIGN = 291,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 292,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 293,              /* MOD_ASSIGN  */
    INCREMENT = 294,               /* INCREMENT  */
    DECREMENT = 295,               /* DECREMENT  */
    LT = 296,                      /* LT  */
    GT = 297,                      /* GT  */
    LE = 298,                      /* LE  */
    GE = 299,                      /* GE  */
    EQ = 300,                      /* EQ  */
    NE = 301,                      /* NE  */
    AND = 302,                     /* AND  */
    OR = 303,                      /* OR  */
    NOT = 304,                     /* NOT  */
    BIT_AND = 305,                 /* BIT_AND  */
    BIT_OR = 306,                  /* BIT_OR  */
    BIT_NOT = 307,                 /* BIT_NOT  */
    LSHIFT = 308,                  /* LSHIFT  */
    RSHIFT = 309,                  /* RSHIFT  */
    LPAREN = 310,                  /* LPAREN  */
    RPAREN = 311,                  /* RPAREN  */
    LBRACE = 312,                  /* LBRACE  */
    RBRACE = 313,                  /* RBRACE  */
    LBRACKET = 314,                /* LBRACKET  */
    RBRACKET = 315,                /* RBRACKET  */
    SEMICOLON = 316,               /* SEMICOLON  */
    COMMA = 317,                   /* COMMA  */
    COLON = 318,                   /* COLON  */
    UMINUS = 319,                  /* UMINUS  */
    LOWER_THAN_ELSE = 320          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define STRING_CONST 259
#define INT_CONST 260
#define FLOAT_CONST 261
#define BOOL_CONST 262
#define INT 263
#define FLOAT 264
#define STRING 265
#define BOOL 266
#define CONST 267
#define IF 268
#define ELSE 269
#define WHILE 270
#define FOR 271
#define DO 272
#define UNTIL 273
#define SWITCH 274
#define CASE 275
#define DEFAULT 276
#define BREAK 277
#define CONTINUE 278
#define RETURN 279
#define FUNCTION 280
#define PRINT 281
#define PLUS 282
#define MINUS 283
#define MULTIPLY 284
#define DIVIDE 285
#define MODULO 286
#define POWER 287
#define ASSIGN 288
#define PLUS_ASSIGN 289
#define MINUS_ASSIGN 290
#define MUL_ASSIGN 291
#define DIV_ASSIGN 292
#define MOD_ASSIGN 293
#define INCREMENT 294
#define DECREMENT 295
#define LT 296
#define GT 297
#define LE 298
#define GE 299
#define EQ 300
#define NE 301
#define AND 302
#define OR 303
#define NOT 304
#define BIT_AND 305
#define BIT_OR 306
#define BIT_NOT 307
#define LSHIFT 308
#define RSHIFT 309
#define LPAREN 310
#define RPAREN 311
#define LBRACE 312
#define RBRACE 313
#define LBRACKET 314
#define RBRACKET 315
#define SEMICOLON 316
#define COMMA 317
#define COLON 318
#define UMINUS 319
#define LOWER_THAN_ELSE 320

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 72 "simplelang.y"

    int ival;
    float fval;
    char *sval;
    int bval;
    val *vval;
    Parameter *pval;
    Type tval;

#line 215 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
