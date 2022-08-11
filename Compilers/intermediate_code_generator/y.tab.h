/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    COMMA = 259,
    BLANKID = 260,
    LBRACE = 261,
    LPAR = 262,
    LSQ = 263,
    RBRACE = 264,
    RPAR = 265,
    RSQ = 266,
    PACKAGE = 267,
    ELSE = 268,
    VAR = 269,
    INT = 270,
    FLOAT32 = 271,
    BOOL = 272,
    STRING = 273,
    FUNC = 274,
    CMDARGS = 275,
    RESERVED = 276,
    ID = 277,
    STRLIT = 278,
    INTLIT = 279,
    REALLIT = 280,
    ASSIGN = 281,
    STAR = 282,
    DIV = 283,
    MINUS = 284,
    PLUS = 285,
    EQ = 286,
    GE = 287,
    GT = 288,
    LE = 289,
    LT = 290,
    MOD = 291,
    NE = 292,
    NOT = 293,
    AND = 294,
    OR = 295,
    FOR = 296,
    IF = 297,
    RETURN = 298,
    PARSEINT = 299,
    PRINT = 300
  };
#endif
/* Tokens.  */
#define SEMICOLON 258
#define COMMA 259
#define BLANKID 260
#define LBRACE 261
#define LPAR 262
#define LSQ 263
#define RBRACE 264
#define RPAR 265
#define RSQ 266
#define PACKAGE 267
#define ELSE 268
#define VAR 269
#define INT 270
#define FLOAT32 271
#define BOOL 272
#define STRING 273
#define FUNC 274
#define CMDARGS 275
#define RESERVED 276
#define ID 277
#define STRLIT 278
#define INTLIT 279
#define REALLIT 280
#define ASSIGN 281
#define STAR 282
#define DIV 283
#define MINUS 284
#define PLUS 285
#define EQ 286
#define GE 287
#define GT 288
#define LE 289
#define LT 290
#define MOD 291
#define NE 292
#define NOT 293
#define AND 294
#define OR 295
#define FOR 296
#define IF 297
#define RETURN 298
#define PARSEINT 299
#define PRINT 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 47 "gocompiler.y"

    is_program* ip;
    is_declarations* id;
    is_vardecl* ivd;
    is_funcdecl* ifd;
    is_parameters* p;
    is_varspec* ivs;
    is_varspec_list* ivslist;
    char* t;
    is_funcbody* ifb;
    id_token* token;
    is_parameters_list* pl;
    is_varsandstatements* ivas;
    is_statement* is;
    is_expr* ie;
    is_funcinvocation* ifi;
    is_parseargs* ipa;
    p_statementlist* isl;
    p_bstatementlist* ibsl;
    is_exprlist* iel;

#line 169 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
