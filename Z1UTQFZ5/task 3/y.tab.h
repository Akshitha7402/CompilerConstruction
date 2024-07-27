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

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    T_INTEGER = 259,               /* T_INTEGER  */
    T_REAL = 260,                  /* T_REAL  */
    T_CHAR = 261,                  /* T_CHAR  */
    T_BOOLEAN = 262,               /* T_BOOLEAN  */
    T_ARRAY = 263,                 /* T_ARRAY  */
    NUM = 264,                     /* NUM  */
    CHAR = 265,                    /* CHAR  */
    FLOAT = 266,                   /* FLOAT  */
    MSG = 267,                     /* MSG  */
    SOB = 268,                     /* SOB  */
    SCB = 269,                     /* SCB  */
    T_OF = 270,                    /* T_OF  */
    RANGE = 271,                   /* RANGE  */
    ArrElement = 272,              /* ArrElement  */
    T_TRUE = 273,                  /* T_TRUE  */
    T_FALSE = 274,                 /* T_FALSE  */
    T_STRING = 275,                /* T_STRING  */
    T_AND = 276,                   /* T_AND  */
    T_OR = 277,                    /* T_OR  */
    T_NOT = 278,                   /* T_NOT  */
    T_PROGRAM = 279,               /* T_PROGRAM  */
    T_VAR = 280,                   /* T_VAR  */
    T_FOR = 281,                   /* T_FOR  */
    T_DO = 282,                    /* T_DO  */
    T_WHILE = 283,                 /* T_WHILE  */
    T_BEGIN = 284,                 /* T_BEGIN  */
    T_END = 285,                   /* T_END  */
    T_write = 286,                 /* T_write  */
    T_READ = 287,                  /* T_READ  */
    COMMA = 288,                   /* COMMA  */
    SC = 289,                      /* SC  */
    COL = 290,                     /* COL  */
    DOT = 291,                     /* DOT  */
    MINUS = 292,                   /* MINUS  */
    DIV = 293,                     /* DIV  */
    MUL = 294,                     /* MUL  */
    REM = 295,                     /* REM  */
    EQUAL = 296,                   /* EQUAL  */
    NEQ = 297,                     /* NEQ  */
    LT = 298,                      /* LT  */
    GT = 299,                      /* GT  */
    LE = 300,                      /* LE  */
    GE = 301,                      /* GE  */
    COMMENT = 302,                 /* COMMENT  */
    OB = 303,                      /* OB  */
    CB = 304,                      /* CB  */
    AS = 305,                      /* AS  */
    PLUS = 306,                    /* PLUS  */
    T_TO = 307,                    /* T_TO  */
    T_ELSE = 308,                  /* T_ELSE  */
    T_THEN = 309,                  /* T_THEN  */
    T_IF = 310,                    /* T_IF  */
    T_DOWNTO = 311                 /* T_DOWNTO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define T_INTEGER 259
#define T_REAL 260
#define T_CHAR 261
#define T_BOOLEAN 262
#define T_ARRAY 263
#define NUM 264
#define CHAR 265
#define FLOAT 266
#define MSG 267
#define SOB 268
#define SCB 269
#define T_OF 270
#define RANGE 271
#define ArrElement 272
#define T_TRUE 273
#define T_FALSE 274
#define T_STRING 275
#define T_AND 276
#define T_OR 277
#define T_NOT 278
#define T_PROGRAM 279
#define T_VAR 280
#define T_FOR 281
#define T_DO 282
#define T_WHILE 283
#define T_BEGIN 284
#define T_END 285
#define T_write 286
#define T_READ 287
#define COMMA 288
#define SC 289
#define COL 290
#define DOT 291
#define MINUS 292
#define DIV 293
#define MUL 294
#define REM 295
#define EQUAL 296
#define NEQ 297
#define LT 298
#define GT 299
#define LE 300
#define GE 301
#define COMMENT 302
#define OB 303
#define CB 304
#define AS 305
#define PLUS 306
#define T_TO 307
#define T_ELSE 308
#define T_THEN 309
#define T_IF 310
#define T_DOWNTO 311

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 502 "Z1UTQFZ5.y"
 
  struct { 
    char type[10]; 
    char *code; //for storing t0,t1,...
    union { 
      char *string;      
      int ival;
      int c1;
      int c2;
      float fval; 
      char cval; 
      char *op;
      int bval;
    } v; 
  } t; 

#line 196 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
