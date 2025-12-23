/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "simplelang.y"

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

#line 132 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 173 "y.tab.c"

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

#line 333 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING_CONST = 4,               /* STRING_CONST  */
  YYSYMBOL_INT_CONST = 5,                  /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 6,                /* FLOAT_CONST  */
  YYSYMBOL_BOOL_CONST = 7,                 /* BOOL_CONST  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_FLOAT = 9,                      /* FLOAT  */
  YYSYMBOL_STRING = 10,                    /* STRING  */
  YYSYMBOL_BOOL = 11,                      /* BOOL  */
  YYSYMBOL_CONST = 12,                     /* CONST  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_DO = 17,                        /* DO  */
  YYSYMBOL_UNTIL = 18,                     /* UNTIL  */
  YYSYMBOL_SWITCH = 19,                    /* SWITCH  */
  YYSYMBOL_CASE = 20,                      /* CASE  */
  YYSYMBOL_DEFAULT = 21,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 22,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 23,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 24,                    /* RETURN  */
  YYSYMBOL_FUNCTION = 25,                  /* FUNCTION  */
  YYSYMBOL_PRINT = 26,                     /* PRINT  */
  YYSYMBOL_PLUS = 27,                      /* PLUS  */
  YYSYMBOL_MINUS = 28,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 29,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 30,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 31,                    /* MODULO  */
  YYSYMBOL_POWER = 32,                     /* POWER  */
  YYSYMBOL_ASSIGN = 33,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 34,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 35,              /* MINUS_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 36,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 37,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 38,                /* MOD_ASSIGN  */
  YYSYMBOL_INCREMENT = 39,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 40,                 /* DECREMENT  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_EQ = 45,                        /* EQ  */
  YYSYMBOL_NE = 46,                        /* NE  */
  YYSYMBOL_AND = 47,                       /* AND  */
  YYSYMBOL_OR = 48,                        /* OR  */
  YYSYMBOL_NOT = 49,                       /* NOT  */
  YYSYMBOL_BIT_AND = 50,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 51,                    /* BIT_OR  */
  YYSYMBOL_BIT_NOT = 52,                   /* BIT_NOT  */
  YYSYMBOL_LSHIFT = 53,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 54,                    /* RSHIFT  */
  YYSYMBOL_LPAREN = 55,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 56,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 57,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 58,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 59,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 60,                  /* RBRACKET  */
  YYSYMBOL_SEMICOLON = 61,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 62,                     /* COMMA  */
  YYSYMBOL_COLON = 63,                     /* COLON  */
  YYSYMBOL_UMINUS = 64,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 65,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_program = 67,                   /* program  */
  YYSYMBOL_68_1 = 68,                      /* $@1  */
  YYSYMBOL_declarations = 69,              /* declarations  */
  YYSYMBOL_declaration = 70,               /* declaration  */
  YYSYMBOL_type_specifier = 71,            /* type_specifier  */
  YYSYMBOL_function_definition = 72,       /* function_definition  */
  YYSYMBOL_73_2 = 73,                      /* $@2  */
  YYSYMBOL_74_3 = 74,                      /* $@3  */
  YYSYMBOL_parameter_list = 75,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 76,     /* parameter_declaration  */
  YYSYMBOL_statement = 77,                 /* statement  */
  YYSYMBOL_expression_statement = 78,      /* expression_statement  */
  YYSYMBOL_assignment_statement = 79,      /* assignment_statement  */
  YYSYMBOL_block = 80,                     /* block  */
  YYSYMBOL_81_4 = 81,                      /* $@4  */
  YYSYMBOL_statement_list = 82,            /* statement_list  */
  YYSYMBOL_if_statement = 83,              /* if_statement  */
  YYSYMBOL_84_5 = 84,                      /* $@5  */
  YYSYMBOL_85_6 = 85,                      /* $@6  */
  YYSYMBOL_86_7 = 86,                      /* $@7  */
  YYSYMBOL_while_statement = 87,           /* while_statement  */
  YYSYMBOL_88_8 = 88,                      /* @8  */
  YYSYMBOL_89_9 = 89,                      /* @9  */
  YYSYMBOL_do_while_statement = 90,        /* do_while_statement  */
  YYSYMBOL_91_10 = 91,                     /* @10  */
  YYSYMBOL_for_statement = 92,             /* for_statement  */
  YYSYMBOL_for_init = 93,                  /* for_init  */
  YYSYMBOL_for_condition = 94,             /* for_condition  */
  YYSYMBOL_for_update = 95,                /* for_update  */
  YYSYMBOL_switch_statement = 96,          /* switch_statement  */
  YYSYMBOL_97_11 = 97,                     /* $@11  */
  YYSYMBOL_case_list = 98,                 /* case_list  */
  YYSYMBOL_case_item = 99,                 /* case_item  */
  YYSYMBOL_100_12 = 100,                   /* @12  */
  YYSYMBOL_101_13 = 101,                   /* @13  */
  YYSYMBOL_break_statement = 102,          /* break_statement  */
  YYSYMBOL_continue_statement = 103,       /* continue_statement  */
  YYSYMBOL_return_statement = 104,         /* return_statement  */
  YYSYMBOL_print_statement = 105,          /* print_statement  */
  YYSYMBOL_expression = 106,               /* expression  */
  YYSYMBOL_logical_or_expr = 107,          /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 108,         /* logical_and_expr  */
  YYSYMBOL_equality_expr = 109,            /* equality_expr  */
  YYSYMBOL_relational_expr = 110,          /* relational_expr  */
  YYSYMBOL_additive_expr = 111,            /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 112,      /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 113,               /* unary_expr  */
  YYSYMBOL_primary_expr = 114,             /* primary_expr  */
  YYSYMBOL_function_call = 115,            /* function_call  */
  YYSYMBOL_argument_list = 116             /* argument_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   508

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  215

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   145,   145,   145,   183,   185,   186,   187,   195,   205,
     244,   284,   285,   286,   287,   296,   295,   317,   316,   335,
     337,   342,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   368,   374,   383,   384,   385,   389,
     410,   427,   444,   461,   482,   481,   514,   516,   525,   524,
     538,   547,   537,   560,   568,   559,   586,   585,   606,   618,
     620,   621,   636,   637,   640,   642,   643,   657,   675,   674,
     691,   693,   698,   697,   713,   712,   726,   730,   741,   752,
     761,   776,   781,   793,   797,   798,   807,   808,   817,   818,
     824,   833,   834,   840,   846,   852,   861,   862,   868,   877,
     878,   884,   890,   899,   900,   913,   921,   937,   956,   957,
     974,   978,   982,   987,   991,   995,  1028,  1054,  1062
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "STRING_CONST", "INT_CONST", "FLOAT_CONST", "BOOL_CONST", "INT", "FLOAT",
  "STRING", "BOOL", "CONST", "IF", "ELSE", "WHILE", "FOR", "DO", "UNTIL",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN", "FUNCTION",
  "PRINT", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "POWER",
  "ASSIGN", "PLUS_ASSIGN", "MINUS_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "INCREMENT", "DECREMENT", "LT", "GT", "LE", "GE", "EQ",
  "NE", "AND", "OR", "NOT", "BIT_AND", "BIT_OR", "BIT_NOT", "LSHIFT",
  "RSHIFT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
  "SEMICOLON", "COMMA", "COLON", "UMINUS", "LOWER_THAN_ELSE", "$accept",
  "program", "$@1", "declarations", "declaration", "type_specifier",
  "function_definition", "$@2", "$@3", "parameter_list",
  "parameter_declaration", "statement", "expression_statement",
  "assignment_statement", "block", "$@4", "statement_list", "if_statement",
  "$@5", "$@6", "$@7", "while_statement", "@8", "@9", "do_while_statement",
  "@10", "for_statement", "for_init", "for_condition", "for_update",
  "switch_statement", "$@11", "case_list", "case_item", "@12", "@13",
  "break_statement", "continue_statement", "return_statement",
  "print_statement", "expression", "logical_or_expr", "logical_and_expr",
  "equality_expr", "relational_expr", "additive_expr",
  "multiplicative_expr", "unary_expr", "primary_expr", "function_call",
  "argument_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-166)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-77)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -166,     5,  -166,  -166,   191,    -6,   127,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,   145,   -24,  -166,     1,  -166,
       4,   -15,    11,    22,   131,   453,    50,    75,   453,   453,
    -166,  -166,  -166,    84,  -166,  -166,  -166,    29,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,    48,    45,
      64,    -7,   134,    37,    -8,  -166,  -166,  -166,  -166,  -166,
     453,   453,   453,   453,   453,    30,   113,   453,    63,    65,
     427,   453,  -166,  -166,    77,  -166,    72,   453,    78,  -166,
    -166,  -166,  -166,    85,  -166,    -1,  -166,  -166,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,  -166,  -166,  -166,  -166,  -166,  -166,  -166,   -48,   109,
      87,   453,   132,   142,  -166,    89,  -166,   148,   158,   123,
    -166,   125,  -166,  -166,    91,   453,     7,  -166,    64,    -7,
     134,   134,    37,    37,    37,    37,    -8,    -8,  -166,  -166,
    -166,  -166,   453,   453,  -166,   128,   150,   453,   -13,   130,
    -166,   126,  -166,  -166,   144,  -166,   185,   -32,  -166,  -166,
     151,   427,   427,  -166,   453,   155,  -166,   453,   152,  -166,
    -166,   154,  -166,  -166,   145,  -166,  -166,   175,   427,  -166,
     215,   169,  -166,  -166,   154,  -166,  -166,  -166,   187,  -166,
     172,   168,    -9,  -166,   427,  -166,  -166,   427,  -166,   116,
     173,  -166,  -166,  -166,  -166,   174,   176,  -166,  -166,  -166,
     250,  -166,  -166,   309,   368
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     4,     1,     0,     0,   109,   112,   110,   111,
     113,    11,    12,    13,    14,     0,     0,    53,     0,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      44,    36,     5,     0,     6,     7,    22,     0,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     0,    83,
      84,    86,    88,    91,    96,    99,   103,   114,    35,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    59,
       0,     0,    77,    78,   109,    79,     0,     0,     0,   104,
     106,   107,   105,     0,    46,     0,    38,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    39,    40,    41,    42,    43,   116,   117,     0,     0,
       0,     0,     0,     0,    60,     0,    23,     0,     0,     0,
      80,     0,    81,   108,     0,     0,     0,     8,    85,    87,
      89,    90,    92,    93,    94,    95,    97,    98,   100,   101,
     102,   115,     0,     0,    48,     0,     0,    62,     0,     0,
      68,   108,    45,    47,     0,    17,     0,     0,    19,   118,
       0,     0,     0,    54,     0,     0,    63,     0,     0,    82,
       9,     0,    21,    15,     0,    10,    49,     0,     0,    61,
      64,     0,    70,    18,     0,    20,    51,    55,     0,    65,
       0,     0,     0,    16,     0,    66,    67,     0,    57,     0,
       0,    69,    71,    52,    58,     0,     0,    46,    74,    72,
       0,    46,    46,     0,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,  -166,  -166,   234,    -2,  -166,  -166,  -166,  -166,
      67,    -4,  -166,   -68,  -165,  -166,  -123,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
     -20,  -166,   156,   153,    35,   140,    32,   -18,  -166,  -166,
    -166
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     4,   116,   117,    34,   184,   171,   157,
     158,   153,    36,    37,    38,    84,   124,    39,   161,   162,
     194,    40,    68,   178,    41,    70,    42,   115,   165,   190,
      43,   168,   192,   202,   212,   211,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
     108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,   114,    33,    76,    78,     3,   183,    79,   141,    83,
      82,   199,   200,    66,   142,    11,    12,    13,    14,   193,
     125,    98,    99,   100,   173,    74,     7,     8,     9,    10,
     174,    67,   125,    74,     7,     8,     9,    10,    90,    91,
     101,   102,   103,   104,   105,   107,    72,   110,   127,   201,
      25,   119,    58,    80,   126,    59,    69,   121,    25,    71,
     127,    26,    27,   155,    96,    97,   118,   113,   112,    26,
      27,    28,    73,    11,    12,    13,    14,    29,    81,    28,
     138,   139,   140,    75,   210,    29,   106,    85,   213,   214,
      86,   145,     5,    88,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,   154,    17,    18,    19,    87,
      20,    89,   189,    21,    22,    23,   109,    24,   111,    25,
     205,   206,   159,   160,   156,   130,   131,   166,   136,   137,
      26,    27,    65,   120,    74,     7,     8,     9,    10,   122,
      28,   123,   143,   144,   179,   146,    29,   181,    30,   152,
     147,   148,    31,    11,    12,    13,    14,   176,   177,    25,
      60,    61,    62,    63,    64,    60,    61,    62,    63,    64,
      26,    27,   156,   149,   187,    92,    93,    94,    95,   150,
      28,   151,    65,   164,   163,   167,    77,   169,   172,   186,
     203,    -3,     5,   204,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,   170,    17,    18,    19,   182,
      20,    30,   175,    21,    22,    23,   180,    24,   188,    25,
      60,    61,    62,    63,    64,   191,   195,   196,   197,   198,
      26,    27,   132,   133,   134,   135,   207,   208,    32,   209,
      28,   185,   129,     0,   128,     0,    29,     0,    30,     0,
       0,     5,    31,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,     0,    17,    18,    19,     0,    20,
     -76,   -76,    21,    22,    23,     0,    24,     0,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
      27,     0,     0,     0,     0,     0,     0,     0,     0,    28,
       0,     0,     0,     0,     0,    29,     0,    30,   -76,     0,
       5,    31,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,     0,    17,    18,    19,     0,    20,   -75,
     -75,    21,    22,    23,     0,    24,     0,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,    27,
       0,     0,     0,     0,     0,     0,     0,     0,    28,     0,
       0,     0,     0,     0,    29,     0,    30,   -75,     0,     5,
      31,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,     0,    17,    18,    19,     0,    20,   -73,   -73,
      21,    22,    23,     0,    24,     0,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,     0,
       0,     0,     0,    29,     0,    30,   -73,     0,     5,    31,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     0,    17,    18,    19,     0,    20,     0,     0,    21,
      22,    23,     0,    24,     0,    25,    74,     7,     8,     9,
      10,     0,     0,     0,     0,     0,    26,    27,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,     0,     0,
       0,    25,    29,     0,    30,     0,     0,     0,    31,     0,
       0,     0,    26,    27,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,     0,     0,     0,     0,    29
};

static const yytype_int16 yycheck[] =
{
       4,    69,     4,    23,    24,     0,   171,    25,    56,    29,
      28,    20,    21,    15,    62,     8,     9,    10,    11,   184,
      33,    29,    30,    31,    56,     3,     4,     5,     6,     7,
      62,    55,    33,     3,     4,     5,     6,     7,    45,    46,
      60,    61,    62,    63,    64,    65,    61,    67,    61,    58,
      28,    71,    58,     3,    55,    61,    55,    77,    28,    55,
      61,    39,    40,    56,    27,    28,    70,    69,     3,    39,
      40,    49,    61,     8,     9,    10,    11,    55,     3,    49,
      98,    99,   100,    61,   207,    55,    56,     3,   211,   212,
      61,   111,     1,    48,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   125,    15,    16,    17,    61,
      19,    47,   180,    22,    23,    24,     3,    26,    55,    28,
       4,     5,   142,   143,   126,    90,    91,   147,    96,    97,
      39,    40,    55,    61,     3,     4,     5,     6,     7,    61,
      49,    56,    33,    56,   164,     3,    55,   167,    57,    58,
      61,     3,    61,     8,     9,    10,    11,   161,   162,    28,
      33,    34,    35,    36,    37,    33,    34,    35,    36,    37,
      39,    40,   174,    15,   178,    41,    42,    43,    44,    56,
      49,    56,    55,    33,    56,    55,    55,    61,     3,    14,
     194,     0,     1,   197,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    61,    15,    16,    17,    57,
      19,    57,    61,    22,    23,    24,    61,    26,     3,    28,
      33,    34,    35,    36,    37,    56,    39,    40,    56,    61,
      39,    40,    92,    93,    94,    95,    63,    63,     4,    63,
      49,   174,    89,    -1,    88,    -1,    55,    -1,    57,    -1,
      -1,     1,    61,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    -1,    26,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    57,    58,    -1,
       1,    61,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    -1,    26,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    57,    58,    -1,     1,
      61,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    -1,    19,    20,    21,
      22,    23,    24,    -1,    26,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    57,    58,    -1,     1,    61,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    -1,    19,    -1,    -1,    22,
      23,    24,    -1,    26,    -1,    28,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    28,    55,    -1,    57,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    67,    68,     0,    69,     1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    15,    16,    17,
      19,    22,    23,    24,    26,    28,    39,    40,    49,    55,
      57,    61,    70,    71,    72,    77,    78,    79,    80,    83,
      87,    90,    92,    96,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    58,    61,
      33,    34,    35,    36,    37,    55,    71,    55,    88,    55,
      91,    55,    61,    61,     3,    61,   106,    55,   106,   113,
       3,     3,   113,   106,    81,     3,    61,    61,    48,    47,
      45,    46,    41,    42,    43,    44,    27,    28,    29,    30,
      31,   106,   106,   106,   106,   106,    56,   106,   116,     3,
     106,    55,     3,    71,    79,    93,    70,    71,    77,   106,
      61,   106,    61,    56,    82,    33,    55,    61,   108,   109,
     110,   110,   111,   111,   111,   111,   112,   112,   113,   113,
     113,    56,    62,    33,    56,   106,     3,    61,     3,    15,
      56,    56,    58,    77,   106,    56,    71,    75,    76,   106,
     106,    84,    85,    56,    33,    94,   106,    55,    97,    61,
      61,    74,     3,    56,    62,    61,    77,    77,    89,   106,
      61,   106,    57,    80,    73,    76,    14,    77,     3,    79,
      95,    56,    98,    80,    86,    39,    40,    56,    61,    20,
      21,    58,    99,    77,    77,     4,     5,    63,    63,    63,
      82,   101,   100,    82,    82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    68,    67,    69,    69,    69,    69,    70,    70,
      70,    71,    71,    71,    71,    73,    72,    74,    72,    75,
      75,    76,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    78,    78,    78,    79,
      79,    79,    79,    79,    81,    80,    82,    82,    84,    83,
      85,    86,    83,    88,    89,    87,    91,    90,    92,    93,
      93,    93,    94,    94,    95,    95,    95,    95,    97,    96,
      98,    98,   100,    99,   101,    99,    99,   102,   103,   104,
     104,   105,   105,   106,   107,   107,   108,   108,   109,   109,
     109,   110,   110,   110,   110,   110,   111,   111,   111,   112,
     112,   112,   112,   113,   113,   113,   113,   113,   114,   114,
     114,   114,   114,   114,   114,   115,   115,   116,   116
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     2,     2,     3,     5,
       6,     1,     1,     1,     1,     0,     7,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     2,     3,
       3,     3,     3,     3,     0,     4,     0,     2,     0,     6,
       0,     0,     9,     0,     0,     7,     0,     8,     9,     0,
       1,     4,     0,     1,     0,     1,     2,     2,     0,     8,
       0,     2,     0,     5,     0,     5,     3,     2,     2,     2,
       3,     3,     5,     1,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     2,     2,     2,     2,     3,     1,
       1,     1,     1,     1,     1,     4,     3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 145 "simplelang.y"
    { 
        // Initialize global scope
        global_scope = create_symbol_table(NULL);
        current_scope = global_scope;
    }
#line 1921 "y.tab.c"
    break;

  case 3: /* program: $@1 declarations  */
#line 151 "simplelang.y"
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
#line 1956 "y.tab.c"
    break;

  case 8: /* declaration: type_specifier IDENTIFIER SEMICOLON  */
#line 196 "simplelang.y"
    {
        val *v = create_val((yyvsp[-2].tval));
        v->place = strdup((yyvsp[-1].sval));
        Symbol *sym = insert_symbol(current_scope, (yyvsp[-1].sval), v, SYM_VARIABLE, 0, NULL, yylineno);
        if (sym) {
            add_quad("DECL", type_to_string((yyvsp[-2].tval)), "", (yyvsp[-1].sval));
        }
        free((yyvsp[-1].sval));
    }
#line 1970 "y.tab.c"
    break;

  case 9: /* declaration: type_specifier IDENTIFIER ASSIGN expression SEMICOLON  */
#line 206 "simplelang.y"
    {
        // Check type compatibility
        if (!check_assignment_type((yyvsp[-4].tval), (yyvsp[-1].vval)->type)) {
            semantic_error(yylineno, "Type mismatch in initialization: cannot assign %s to %s",
                          type_to_string((yyvsp[-1].vval)->type), type_to_string((yyvsp[-4].tval)));
        }
        
        val *v = create_val((yyvsp[-4].tval));
        v->place = strdup((yyvsp[-3].sval));
        
        // Copy value
        switch ((yyvsp[-4].tval)) {
            case TYPE_INT:
                v->data.i = ((yyvsp[-1].vval)->type == TYPE_FLOAT) ? (int)(yyvsp[-1].vval)->data.f : (yyvsp[-1].vval)->data.i;
                break;
            case TYPE_FLOAT:
                v->data.f = ((yyvsp[-1].vval)->type == TYPE_INT) ? (float)(yyvsp[-1].vval)->data.i : (yyvsp[-1].vval)->data.f;
                break;
            case TYPE_STRING:
                if ((yyvsp[-1].vval)->data.s) v->data.s = strdup((yyvsp[-1].vval)->data.s);
                break;
            case TYPE_BOOL:
                v->data.b = (yyvsp[-1].vval)->data.b;
                break;
            default:
                break;
        }
        
        Symbol *sym = insert_symbol(current_scope, (yyvsp[-3].sval), v, SYM_VARIABLE, 0, NULL, yylineno);
        if (sym) {
            sym->is_initialized = true;
            add_quad("DECL", type_to_string((yyvsp[-4].tval)), "", (yyvsp[-3].sval));
            add_quad("ASSIGN", (yyvsp[-1].vval)->place, "", (yyvsp[-3].sval));
        }
        
        free((yyvsp[-3].sval));
        free_val((yyvsp[-1].vval));
    }
#line 2013 "y.tab.c"
    break;

  case 10: /* declaration: CONST type_specifier IDENTIFIER ASSIGN expression SEMICOLON  */
#line 245 "simplelang.y"
    {
        // Constants must be initialized
        if (!check_assignment_type((yyvsp[-4].tval), (yyvsp[-1].vval)->type)) {
            semantic_error(yylineno, "Type mismatch in constant initialization");
        }
        
        val *v = create_val((yyvsp[-4].tval));
        v->place = strdup((yyvsp[-3].sval));
        v->is_constant = true;
        
        switch ((yyvsp[-4].tval)) {
            case TYPE_INT:
                v->data.i = ((yyvsp[-1].vval)->type == TYPE_FLOAT) ? (int)(yyvsp[-1].vval)->data.f : (yyvsp[-1].vval)->data.i;
                break;
            case TYPE_FLOAT:
                v->data.f = ((yyvsp[-1].vval)->type == TYPE_INT) ? (float)(yyvsp[-1].vval)->data.i : (yyvsp[-1].vval)->data.f;
                break;
            case TYPE_STRING:
                if ((yyvsp[-1].vval)->data.s) v->data.s = strdup((yyvsp[-1].vval)->data.s);
                break;
            case TYPE_BOOL:
                v->data.b = (yyvsp[-1].vval)->data.b;
                break;
            default:
                break;
        }
        
        Symbol *sym = insert_symbol(current_scope, (yyvsp[-3].sval), v, SYM_CONSTANT, 0, NULL, yylineno);
        if (sym) {
            sym->is_initialized = true;
            add_quad("CONST", type_to_string((yyvsp[-4].tval)), (yyvsp[-1].vval)->place, (yyvsp[-3].sval));
        }
        
        free((yyvsp[-3].sval));
        free_val((yyvsp[-1].vval));
    }
#line 2054 "y.tab.c"
    break;

  case 11: /* type_specifier: INT  */
#line 284 "simplelang.y"
            { (yyval.tval) = TYPE_INT; }
#line 2060 "y.tab.c"
    break;

  case 12: /* type_specifier: FLOAT  */
#line 285 "simplelang.y"
            { (yyval.tval) = TYPE_FLOAT; }
#line 2066 "y.tab.c"
    break;

  case 13: /* type_specifier: STRING  */
#line 286 "simplelang.y"
             { (yyval.tval) = TYPE_STRING; }
#line 2072 "y.tab.c"
    break;

  case 14: /* type_specifier: BOOL  */
#line 287 "simplelang.y"
            { (yyval.tval) = TYPE_BOOL; }
#line 2078 "y.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 296 "simplelang.y"
    {
        // Create function value
        val *func_val = create_val((yyvsp[-4].tval));
        func_val->place = strdup((yyvsp[-3].sval));
        func_val->endLabel = new_label();
        
        int param_count = count_params((yyvsp[-1].pval));
        Symbol *func = insert_symbol(current_scope, (yyvsp[-3].sval), func_val, SYM_FUNCTION, 
                                     param_count, (yyvsp[-1].pval), yylineno);
        current_function = func;
        current_params = (yyvsp[-1].pval);
        
        add_quad("FUNC", (yyvsp[-3].sval), "", "");
    }
#line 2097 "y.tab.c"
    break;

  case 16: /* function_definition: type_specifier IDENTIFIER LPAREN parameter_list RPAREN $@2 block  */
#line 311 "simplelang.y"
    {
        add_quad("ENDFUNC", (yyvsp[-5].sval), "", "");
        current_function = NULL;
        current_params = NULL;
    }
#line 2107 "y.tab.c"
    break;

  case 17: /* $@3: %empty  */
#line 317 "simplelang.y"
    {
        val *func_val = create_val((yyvsp[-3].tval));
        func_val->place = strdup((yyvsp[-2].sval));
        func_val->endLabel = new_label();
        
        Symbol *func = insert_symbol(current_scope, (yyvsp[-2].sval), func_val, SYM_FUNCTION, 0, NULL, yylineno);
        current_function = func;
        
        add_quad("FUNC", (yyvsp[-2].sval), "", "");
    }
#line 2122 "y.tab.c"
    break;

  case 18: /* function_definition: type_specifier IDENTIFIER LPAREN RPAREN $@3 block  */
#line 328 "simplelang.y"
    {
        add_quad("ENDFUNC", (yyvsp[-4].sval), "", "");
        current_function = NULL;
    }
#line 2131 "y.tab.c"
    break;

  case 19: /* parameter_list: parameter_declaration  */
#line 336 "simplelang.y"
    { (yyval.pval) = (yyvsp[0].pval); }
#line 2137 "y.tab.c"
    break;

  case 20: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 338 "simplelang.y"
    { (yyval.pval) = append_param((yyvsp[-2].pval), (yyvsp[0].pval)); }
#line 2143 "y.tab.c"
    break;

  case 21: /* parameter_declaration: type_specifier IDENTIFIER  */
#line 343 "simplelang.y"
    {
        val *v = create_val((yyvsp[-1].tval));
        v->place = strdup((yyvsp[0].sval));
        (yyval.pval) = create_param((yyvsp[0].sval), v);
        free((yyvsp[0].sval));
    }
#line 2154 "y.tab.c"
    break;

  case 34: /* statement: error SEMICOLON  */
#line 369 "simplelang.y"
    {
        fprintf(stderr, "Syntax error recovered at line %d\n", yylineno);
        syntax_error_count++;
        yyerrok;
    }
#line 2164 "y.tab.c"
    break;

  case 35: /* statement: error RBRACE  */
#line 375 "simplelang.y"
    {
        fprintf(stderr, "Syntax error recovered at block end, line %d\n", yylineno);
        syntax_error_count++;
        yyerrok;
    }
#line 2174 "y.tab.c"
    break;

  case 37: /* expression_statement: expression SEMICOLON  */
#line 384 "simplelang.y"
                           { free_val((yyvsp[-1].vval)); }
#line 2180 "y.tab.c"
    break;

  case 39: /* assignment_statement: IDENTIFIER ASSIGN expression  */
#line 390 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[-2].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[-2].sval));
        } else {
            sym->is_used = true;
            
            if (sym->sym_type == SYM_CONSTANT) {
                semantic_error(yylineno, "Cannot assign to constant '%s'", (yyvsp[-2].sval));
            } else {
                if (!check_assignment_type(sym->value->type, (yyvsp[0].vval)->type)) {
                    semantic_error(yylineno, "Type mismatch in assignment to '%s'", (yyvsp[-2].sval));
                }
                sym->is_initialized = true;
                add_quad("ASSIGN", (yyvsp[0].vval)->place, "", (yyvsp[-2].sval));
            }
        }
        free((yyvsp[-2].sval));
        free_val((yyvsp[0].vval));
    }
#line 2205 "y.tab.c"
    break;

  case 40: /* assignment_statement: IDENTIFIER PLUS_ASSIGN expression  */
#line 411 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[-2].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[-2].sval));
        } else if (sym->sym_type == SYM_CONSTANT) {
            semantic_error(yylineno, "Cannot modify constant '%s'", (yyvsp[-2].sval));
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("ADD", (yyvsp[-2].sval), (yyvsp[0].vval)->place, temp);
            add_quad("ASSIGN", temp, "", (yyvsp[-2].sval));
            free(temp);
        }
        free((yyvsp[-2].sval));
        free_val((yyvsp[0].vval));
    }
#line 2226 "y.tab.c"
    break;

  case 41: /* assignment_statement: IDENTIFIER MINUS_ASSIGN expression  */
#line 428 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[-2].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[-2].sval));
        } else if (sym->sym_type == SYM_CONSTANT) {
            semantic_error(yylineno, "Cannot modify constant '%s'", (yyvsp[-2].sval));
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("SUB", (yyvsp[-2].sval), (yyvsp[0].vval)->place, temp);
            add_quad("ASSIGN", temp, "", (yyvsp[-2].sval));
            free(temp);
        }
        free((yyvsp[-2].sval));
        free_val((yyvsp[0].vval));
    }
#line 2247 "y.tab.c"
    break;

  case 42: /* assignment_statement: IDENTIFIER MUL_ASSIGN expression  */
#line 445 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[-2].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[-2].sval));
        } else if (sym->sym_type == SYM_CONSTANT) {
            semantic_error(yylineno, "Cannot modify constant '%s'", (yyvsp[-2].sval));
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("MUL", (yyvsp[-2].sval), (yyvsp[0].vval)->place, temp);
            add_quad("ASSIGN", temp, "", (yyvsp[-2].sval));
            free(temp);
        }
        free((yyvsp[-2].sval));
        free_val((yyvsp[0].vval));
    }
#line 2268 "y.tab.c"
    break;

  case 43: /* assignment_statement: IDENTIFIER DIV_ASSIGN expression  */
#line 462 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[-2].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[-2].sval));
        } else if (sym->sym_type == SYM_CONSTANT) {
            semantic_error(yylineno, "Cannot modify constant '%s'", (yyvsp[-2].sval));
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("DIV", (yyvsp[-2].sval), (yyvsp[0].vval)->place, temp);
            add_quad("ASSIGN", temp, "", (yyvsp[-2].sval));
            free(temp);
        }
        free((yyvsp[-2].sval));
        free_val((yyvsp[0].vval));
    }
#line 2289 "y.tab.c"
    break;

  case 44: /* $@4: %empty  */
#line 482 "simplelang.y"
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
#line 2311 "y.tab.c"
    break;

  case 45: /* block: LBRACE $@4 statement_list RBRACE  */
#line 500 "simplelang.y"
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
#line 2328 "y.tab.c"
    break;

  case 48: /* $@5: %empty  */
#line 525 "simplelang.y"
    {
        if ((yyvsp[-1].vval)->type != TYPE_BOOL) {
            semantic_warning(yylineno, "Condition should be boolean type");
        }
        (yyvsp[-1].vval)->falseLabel = new_label();
        add_quad("JMP_FALSE", (yyvsp[-1].vval)->place, "", (yyvsp[-1].vval)->falseLabel);
    }
#line 2340 "y.tab.c"
    break;

  case 49: /* if_statement: IF LPAREN expression RPAREN $@5 statement  */
#line 533 "simplelang.y"
    {
        add_quad("LABEL", (yyvsp[-3].vval)->falseLabel, "", "");
        free_val((yyvsp[-3].vval));
    }
#line 2349 "y.tab.c"
    break;

  case 50: /* $@6: %empty  */
#line 538 "simplelang.y"
    {
        if ((yyvsp[-1].vval)->type != TYPE_BOOL) {
            semantic_warning(yylineno, "Condition should be boolean type");
        }
        (yyvsp[-1].vval)->falseLabel = new_label();
        (yyvsp[-1].vval)->endLabel = new_label();
        add_quad("JMP_FALSE", (yyvsp[-1].vval)->place, "", (yyvsp[-1].vval)->falseLabel);
    }
#line 2362 "y.tab.c"
    break;

  case 51: /* $@7: %empty  */
#line 547 "simplelang.y"
    {
        add_quad("JMP", "", "", (yyvsp[-4].vval)->endLabel);
        add_quad("LABEL", (yyvsp[-4].vval)->falseLabel, "", "");
    }
#line 2371 "y.tab.c"
    break;

  case 52: /* if_statement: IF LPAREN expression RPAREN $@6 statement ELSE $@7 statement  */
#line 552 "simplelang.y"
    {
        add_quad("LABEL", (yyvsp[-6].vval)->endLabel, "", "");
        free_val((yyvsp[-6].vval));
    }
#line 2380 "y.tab.c"
    break;

  case 53: /* @8: %empty  */
#line 560 "simplelang.y"
    {
        char *start_label = new_label();
        char *end_label = new_label();
        push_loop(end_label, start_label);
        add_quad("LABEL", start_label, "", "");
        (yyval.sval) = start_label;
    }
#line 2392 "y.tab.c"
    break;

  case 54: /* @9: %empty  */
#line 568 "simplelang.y"
    {
        if ((yyvsp[-1].vval)->type != TYPE_BOOL) {
            semantic_warning(yylineno, "While condition should be boolean type");
        }
        add_quad("JMP_FALSE", (yyvsp[-1].vval)->place, "", break_label_stack[loop_stack_top]);
        (yyval.vval) = (yyvsp[-1].vval);
    }
#line 2404 "y.tab.c"
    break;

  case 55: /* while_statement: WHILE @8 LPAREN expression RPAREN @9 statement  */
#line 576 "simplelang.y"
    {
        add_quad("JMP", "", "", (yyvsp[-5].sval));
        add_quad("LABEL", break_label_stack[loop_stack_top], "", "");
        pop_loop();
        free_val((yyvsp[-1].vval));
    }
#line 2415 "y.tab.c"
    break;

  case 56: /* @10: %empty  */
#line 586 "simplelang.y"
    {
        char *start_label = new_label();
        char *end_label = new_label();
        push_loop(end_label, start_label);
        add_quad("LABEL", start_label, "", "");
        (yyval.sval) = start_label;
    }
#line 2427 "y.tab.c"
    break;

  case 57: /* do_while_statement: DO @10 statement WHILE LPAREN expression RPAREN SEMICOLON  */
#line 594 "simplelang.y"
    {
        if ((yyvsp[-2].vval)->type != TYPE_BOOL) {
            semantic_warning(yylineno, "Do-while condition should be boolean type");
        }
        add_quad("JMP_TRUE", (yyvsp[-2].vval)->place, "", (yyvsp[-6].sval));
        add_quad("LABEL", break_label_stack[loop_stack_top], "", "");
        pop_loop();
        free_val((yyvsp[-2].vval));
    }
#line 2441 "y.tab.c"
    break;

  case 58: /* for_statement: FOR LPAREN for_init SEMICOLON for_condition SEMICOLON for_update RPAREN statement  */
#line 607 "simplelang.y"
    {
        // For loop code generation simplified for now
        if ((yyvsp[-4].vval)) {
            add_quad("JMP_FALSE", (yyvsp[-4].vval)->place, "", break_label_stack[loop_stack_top]);
            free_val((yyvsp[-4].vval));
        }
        add_quad("LABEL", break_label_stack[loop_stack_top], "", "");
        pop_loop();
    }
#line 2455 "y.tab.c"
    break;

  case 61: /* for_init: type_specifier IDENTIFIER ASSIGN expression  */
#line 622 "simplelang.y"
    {
        val *v = create_val((yyvsp[-3].tval));
        v->place = strdup((yyvsp[-2].sval));
        Symbol *sym = insert_symbol(current_scope, (yyvsp[-2].sval), v, SYM_VARIABLE, 0, NULL, yylineno);
        if (sym) {
            sym->is_initialized = true;
            add_quad("ASSIGN", (yyvsp[0].vval)->place, "", (yyvsp[-2].sval));
        }
        free((yyvsp[-2].sval));
        free_val((yyvsp[0].vval));
    }
#line 2471 "y.tab.c"
    break;

  case 62: /* for_condition: %empty  */
#line 636 "simplelang.y"
                { (yyval.vval) = NULL; }
#line 2477 "y.tab.c"
    break;

  case 63: /* for_condition: expression  */
#line 637 "simplelang.y"
                 { (yyval.vval) = (yyvsp[0].vval); }
#line 2483 "y.tab.c"
    break;

  case 66: /* for_update: IDENTIFIER INCREMENT  */
#line 644 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[-1].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[-1].sval));
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("ADD", (yyvsp[-1].sval), "1", temp);
            add_quad("ASSIGN", temp, "", (yyvsp[-1].sval));
            free(temp);
        }
        free((yyvsp[-1].sval));
    }
#line 2501 "y.tab.c"
    break;

  case 67: /* for_update: IDENTIFIER DECREMENT  */
#line 658 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[-1].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[-1].sval));
        } else {
            sym->is_used = true;
            char *temp = new_temp();
            add_quad("SUB", (yyvsp[-1].sval), "1", temp);
            add_quad("ASSIGN", temp, "", (yyvsp[-1].sval));
            free(temp);
        }
        free((yyvsp[-1].sval));
    }
#line 2519 "y.tab.c"
    break;

  case 68: /* $@11: %empty  */
#line 675 "simplelang.y"
    {
        current_switch_place = (yyvsp[-1].vval)->place;
        current_switch_type = (yyvsp[-1].vval)->type;
        current_switch_end = new_label();
        push_loop(current_switch_end, NULL);  // For break statements
    }
#line 2530 "y.tab.c"
    break;

  case 69: /* switch_statement: SWITCH LPAREN expression RPAREN $@11 LBRACE case_list RBRACE  */
#line 682 "simplelang.y"
    {
        add_quad("LABEL", current_switch_end, "", "");
        pop_loop();
        free_val((yyvsp[-5].vval));
        current_switch_place = NULL;
        current_switch_end = NULL;
    }
#line 2542 "y.tab.c"
    break;

  case 72: /* @12: %empty  */
#line 698 "simplelang.y"
    {
        char buffer[32];
        sprintf(buffer, "%d", (yyvsp[-1].ival));
        char *temp = new_temp();
        add_quad("EQ", current_switch_place, buffer, temp);
        char *next_case = new_label();
        add_quad("JMP_FALSE", temp, "", next_case);
        (yyval.sval) = next_case;
        free(temp);
    }
#line 2557 "y.tab.c"
    break;

  case 73: /* case_item: CASE INT_CONST COLON @12 statement_list  */
#line 709 "simplelang.y"
    {
        add_quad("LABEL", (yyvsp[-1].sval), "", "");
    }
#line 2565 "y.tab.c"
    break;

  case 74: /* @13: %empty  */
#line 713 "simplelang.y"
    {
        char *temp = new_temp();
        add_quad("EQ", current_switch_place, (yyvsp[-1].sval), temp);
        char *next_case = new_label();
        add_quad("JMP_FALSE", temp, "", next_case);
        (yyval.sval) = next_case;
        free(temp);
        free((yyvsp[-1].sval));
    }
#line 2579 "y.tab.c"
    break;

  case 75: /* case_item: CASE STRING_CONST COLON @13 statement_list  */
#line 723 "simplelang.y"
    {
        add_quad("LABEL", (yyvsp[-1].sval), "", "");
    }
#line 2587 "y.tab.c"
    break;

  case 77: /* break_statement: BREAK SEMICOLON  */
#line 731 "simplelang.y"
    {
        if (loop_stack_top < 0) {
            semantic_error(yylineno, "'break' statement not within loop or switch");
        } else {
            add_quad("JMP", "", "", break_label_stack[loop_stack_top]);
        }
    }
#line 2599 "y.tab.c"
    break;

  case 78: /* continue_statement: CONTINUE SEMICOLON  */
#line 742 "simplelang.y"
    {
        if (loop_stack_top < 0 || continue_label_stack[loop_stack_top] == NULL) {
            semantic_error(yylineno, "'continue' statement not within loop");
        } else {
            add_quad("JMP", "", "", continue_label_stack[loop_stack_top]);
        }
    }
#line 2611 "y.tab.c"
    break;

  case 79: /* return_statement: RETURN SEMICOLON  */
#line 753 "simplelang.y"
    {
        if (current_function == NULL) {
            semantic_error(yylineno, "'return' statement outside function");
        } else if (current_function->value->type != TYPE_VOID) {
            semantic_warning(yylineno, "Non-void function should return a value");
        }
        add_quad("RETURN", "", "", "");
    }
#line 2624 "y.tab.c"
    break;

  case 80: /* return_statement: RETURN expression SEMICOLON  */
#line 762 "simplelang.y"
    {
        if (current_function == NULL) {
            semantic_error(yylineno, "'return' statement outside function");
        } else {
            if (!check_assignment_type(current_function->value->type, (yyvsp[-1].vval)->type)) {
                semantic_error(yylineno, "Return type mismatch");
            }
            add_quad("RETURN", (yyvsp[-1].vval)->place, "", "");
        }
        free_val((yyvsp[-1].vval));
    }
#line 2640 "y.tab.c"
    break;

  case 81: /* print_statement: PRINT expression SEMICOLON  */
#line 777 "simplelang.y"
    {
        add_quad("PRINT", (yyvsp[-1].vval)->place, "", "");
        free_val((yyvsp[-1].vval));
    }
#line 2649 "y.tab.c"
    break;

  case 82: /* print_statement: PRINT LPAREN expression RPAREN SEMICOLON  */
#line 782 "simplelang.y"
    {
        add_quad("PRINT", (yyvsp[-2].vval)->place, "", "");
        free_val((yyvsp[-2].vval));
    }
#line 2658 "y.tab.c"
    break;

  case 83: /* expression: logical_or_expr  */
#line 793 "simplelang.y"
                    { (yyval.vval) = (yyvsp[0].vval); }
#line 2664 "y.tab.c"
    break;

  case 84: /* logical_or_expr: logical_and_expr  */
#line 797 "simplelang.y"
                     { (yyval.vval) = (yyvsp[0].vval); }
#line 2670 "y.tab.c"
    break;

  case 85: /* logical_or_expr: logical_or_expr OR logical_and_expr  */
#line 799 "simplelang.y"
    {
        (yyval.vval) = perform_logical((yyvsp[-2].vval), "||", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2680 "y.tab.c"
    break;

  case 86: /* logical_and_expr: equality_expr  */
#line 807 "simplelang.y"
                  { (yyval.vval) = (yyvsp[0].vval); }
#line 2686 "y.tab.c"
    break;

  case 87: /* logical_and_expr: logical_and_expr AND equality_expr  */
#line 809 "simplelang.y"
    {
        (yyval.vval) = perform_logical((yyvsp[-2].vval), "&&", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2696 "y.tab.c"
    break;

  case 88: /* equality_expr: relational_expr  */
#line 817 "simplelang.y"
                    { (yyval.vval) = (yyvsp[0].vval); }
#line 2702 "y.tab.c"
    break;

  case 89: /* equality_expr: equality_expr EQ relational_expr  */
#line 819 "simplelang.y"
    {
        (yyval.vval) = perform_comparison((yyvsp[-2].vval), "==", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2712 "y.tab.c"
    break;

  case 90: /* equality_expr: equality_expr NE relational_expr  */
#line 825 "simplelang.y"
    {
        (yyval.vval) = perform_comparison((yyvsp[-2].vval), "!=", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2722 "y.tab.c"
    break;

  case 91: /* relational_expr: additive_expr  */
#line 833 "simplelang.y"
                  { (yyval.vval) = (yyvsp[0].vval); }
#line 2728 "y.tab.c"
    break;

  case 92: /* relational_expr: relational_expr LT additive_expr  */
#line 835 "simplelang.y"
    {
        (yyval.vval) = perform_comparison((yyvsp[-2].vval), "<", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2738 "y.tab.c"
    break;

  case 93: /* relational_expr: relational_expr GT additive_expr  */
#line 841 "simplelang.y"
    {
        (yyval.vval) = perform_comparison((yyvsp[-2].vval), ">", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2748 "y.tab.c"
    break;

  case 94: /* relational_expr: relational_expr LE additive_expr  */
#line 847 "simplelang.y"
    {
        (yyval.vval) = perform_comparison((yyvsp[-2].vval), "<=", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2758 "y.tab.c"
    break;

  case 95: /* relational_expr: relational_expr GE additive_expr  */
#line 853 "simplelang.y"
    {
        (yyval.vval) = perform_comparison((yyvsp[-2].vval), ">=", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2768 "y.tab.c"
    break;

  case 96: /* additive_expr: multiplicative_expr  */
#line 861 "simplelang.y"
                        { (yyval.vval) = (yyvsp[0].vval); }
#line 2774 "y.tab.c"
    break;

  case 97: /* additive_expr: additive_expr PLUS multiplicative_expr  */
#line 863 "simplelang.y"
    {
        (yyval.vval) = perform_arithmetic((yyvsp[-2].vval), "+", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2784 "y.tab.c"
    break;

  case 98: /* additive_expr: additive_expr MINUS multiplicative_expr  */
#line 869 "simplelang.y"
    {
        (yyval.vval) = perform_arithmetic((yyvsp[-2].vval), "-", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2794 "y.tab.c"
    break;

  case 99: /* multiplicative_expr: unary_expr  */
#line 877 "simplelang.y"
               { (yyval.vval) = (yyvsp[0].vval); }
#line 2800 "y.tab.c"
    break;

  case 100: /* multiplicative_expr: multiplicative_expr MULTIPLY unary_expr  */
#line 879 "simplelang.y"
    {
        (yyval.vval) = perform_arithmetic((yyvsp[-2].vval), "*", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2810 "y.tab.c"
    break;

  case 101: /* multiplicative_expr: multiplicative_expr DIVIDE unary_expr  */
#line 885 "simplelang.y"
    {
        (yyval.vval) = perform_arithmetic((yyvsp[-2].vval), "/", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2820 "y.tab.c"
    break;

  case 102: /* multiplicative_expr: multiplicative_expr MODULO unary_expr  */
#line 891 "simplelang.y"
    {
        (yyval.vval) = perform_arithmetic((yyvsp[-2].vval), "%", (yyvsp[0].vval));
        free_val((yyvsp[-2].vval));
        free_val((yyvsp[0].vval));
    }
#line 2830 "y.tab.c"
    break;

  case 103: /* unary_expr: primary_expr  */
#line 899 "simplelang.y"
                 { (yyval.vval) = (yyvsp[0].vval); }
#line 2836 "y.tab.c"
    break;

  case 104: /* unary_expr: MINUS unary_expr  */
#line 901 "simplelang.y"
    {
        (yyval.vval) = create_val((yyvsp[0].vval)->type);
        (yyval.vval)->place = new_temp();
        add_quad("NEG", (yyvsp[0].vval)->place, "", (yyval.vval)->place);
        
        if ((yyvsp[0].vval)->type == TYPE_INT) {
            (yyval.vval)->data.i = -(yyvsp[0].vval)->data.i;
        } else if ((yyvsp[0].vval)->type == TYPE_FLOAT) {
            (yyval.vval)->data.f = -(yyvsp[0].vval)->data.f;
        }
        free_val((yyvsp[0].vval));
    }
#line 2853 "y.tab.c"
    break;

  case 105: /* unary_expr: NOT unary_expr  */
#line 914 "simplelang.y"
    {
        (yyval.vval) = create_val(TYPE_BOOL);
        (yyval.vval)->place = new_temp();
        add_quad("NOT", (yyvsp[0].vval)->place, "", (yyval.vval)->place);
        (yyval.vval)->data.b = !(yyvsp[0].vval)->data.b;
        free_val((yyvsp[0].vval));
    }
#line 2865 "y.tab.c"
    break;

  case 106: /* unary_expr: INCREMENT IDENTIFIER  */
#line 922 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[0].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[0].sval));
            (yyval.vval) = create_val(TYPE_INT);
        } else {
            sym->is_used = true;
            (yyval.vval) = copy_val(sym->value);
            char *temp = new_temp();
            add_quad("ADD", (yyvsp[0].sval), "1", temp);
            add_quad("ASSIGN", temp, "", (yyvsp[0].sval));
            (yyval.vval)->place = temp;
        }
        free((yyvsp[0].sval));
    }
#line 2885 "y.tab.c"
    break;

  case 107: /* unary_expr: DECREMENT IDENTIFIER  */
#line 938 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[0].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[0].sval));
            (yyval.vval) = create_val(TYPE_INT);
        } else {
            sym->is_used = true;
            (yyval.vval) = copy_val(sym->value);
            char *temp = new_temp();
            add_quad("SUB", (yyvsp[0].sval), "1", temp);
            add_quad("ASSIGN", temp, "", (yyvsp[0].sval));
            (yyval.vval)->place = temp;
        }
        free((yyvsp[0].sval));
    }
#line 2905 "y.tab.c"
    break;

  case 108: /* primary_expr: LPAREN expression RPAREN  */
#line 956 "simplelang.y"
                             { (yyval.vval) = (yyvsp[-1].vval); }
#line 2911 "y.tab.c"
    break;

  case 109: /* primary_expr: IDENTIFIER  */
#line 958 "simplelang.y"
    {
        Symbol *sym = lookup_symbol(current_scope, (yyvsp[0].sval));
        if (!sym) {
            semantic_error(yylineno, "Undefined variable '%s'", (yyvsp[0].sval));
            (yyval.vval) = create_val(TYPE_INT);
            (yyval.vval)->place = strdup((yyvsp[0].sval));
        } else {
            sym->is_used = true;
            if (!sym->is_initialized && sym->sym_type == SYM_VARIABLE) {
                semantic_warning(yylineno, "Variable '%s' may be used uninitialized", (yyvsp[0].sval));
            }
            (yyval.vval) = copy_val(sym->value);
            (yyval.vval)->place = strdup((yyvsp[0].sval));
        }
        free((yyvsp[0].sval));
    }
#line 2932 "y.tab.c"
    break;

  case 110: /* primary_expr: INT_CONST  */
#line 975 "simplelang.y"
    {
        (yyval.vval) = create_int_val((yyvsp[0].ival));
    }
#line 2940 "y.tab.c"
    break;

  case 111: /* primary_expr: FLOAT_CONST  */
#line 979 "simplelang.y"
    {
        (yyval.vval) = create_float_val((yyvsp[0].fval));
    }
#line 2948 "y.tab.c"
    break;

  case 112: /* primary_expr: STRING_CONST  */
#line 983 "simplelang.y"
    {
        (yyval.vval) = create_string_val((yyvsp[0].sval));
        free((yyvsp[0].sval));
    }
#line 2957 "y.tab.c"
    break;

  case 113: /* primary_expr: BOOL_CONST  */
#line 988 "simplelang.y"
    {
        (yyval.vval) = create_bool_val((yyvsp[0].bval));
    }
#line 2965 "y.tab.c"
    break;

  case 114: /* primary_expr: function_call  */
#line 991 "simplelang.y"
                    { (yyval.vval) = (yyvsp[0].vval); }
#line 2971 "y.tab.c"
    break;

  case 115: /* function_call: IDENTIFIER LPAREN argument_list RPAREN  */
#line 996 "simplelang.y"
    {
        Symbol *func = lookup_symbol(current_scope, (yyvsp[-3].sval));
        if (!func) {
            semantic_error(yylineno, "Undefined function '%s'", (yyvsp[-3].sval));
            (yyval.vval) = create_val(TYPE_INT);
        } else if (func->sym_type != SYM_FUNCTION) {
            semantic_error(yylineno, "'%s' is not a function", (yyvsp[-3].sval));
            (yyval.vval) = create_val(TYPE_INT);
        } else {
            func->is_used = true;
            
            // Validate arguments
            int arg_count = count_params((yyvsp[-1].pval));
            if (arg_count != func->param_count) {
                semantic_error(yylineno, "Function '%s' expects %d arguments, got %d",
                              (yyvsp[-3].sval), func->param_count, arg_count);
            }
            
            // Generate parameter passing quads
            Parameter *arg = (yyvsp[-1].pval);
            while (arg) {
                add_quad("ARG", arg->value->place, "", "");
                arg = arg->next;
            }
            
            (yyval.vval) = create_val(func->value->type);
            (yyval.vval)->place = new_temp();
            add_quad("CALL", (yyvsp[-3].sval), "", (yyval.vval)->place);
        }
        free((yyvsp[-3].sval));
        free_params((yyvsp[-1].pval));
    }
#line 3008 "y.tab.c"
    break;

  case 116: /* function_call: IDENTIFIER LPAREN RPAREN  */
#line 1029 "simplelang.y"
    {
        Symbol *func = lookup_symbol(current_scope, (yyvsp[-2].sval));
        if (!func) {
            semantic_error(yylineno, "Undefined function '%s'", (yyvsp[-2].sval));
            (yyval.vval) = create_val(TYPE_INT);
        } else if (func->sym_type != SYM_FUNCTION) {
            semantic_error(yylineno, "'%s' is not a function", (yyvsp[-2].sval));
            (yyval.vval) = create_val(TYPE_INT);
        } else {
            func->is_used = true;
            
            if (func->param_count != 0) {
                semantic_error(yylineno, "Function '%s' expects %d arguments, got 0",
                              (yyvsp[-2].sval), func->param_count);
            }
            
            (yyval.vval) = create_val(func->value->type);
            (yyval.vval)->place = new_temp();
            add_quad("CALL", (yyvsp[-2].sval), "", (yyval.vval)->place);
        }
        free((yyvsp[-2].sval));
    }
#line 3035 "y.tab.c"
    break;

  case 117: /* argument_list: expression  */
#line 1055 "simplelang.y"
    {
        Parameter *p = (Parameter*)malloc(sizeof(Parameter));
        p->name = new_temp();
        p->value = (yyvsp[0].vval);
        p->next = NULL;
        (yyval.pval) = p;
    }
#line 3047 "y.tab.c"
    break;

  case 118: /* argument_list: argument_list COMMA expression  */
#line 1063 "simplelang.y"
    {
        Parameter *p = (Parameter*)malloc(sizeof(Parameter));
        p->name = new_temp();
        p->value = (yyvsp[0].vval);
        p->next = NULL;
        (yyval.pval) = append_param((yyvsp[-2].pval), p);
    }
#line 3059 "y.tab.c"
    break;


#line 3063 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1072 "simplelang.y"


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
