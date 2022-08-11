/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

// Libraries
#include "symbol_table.h"

typedef struct _s3 is_vardecl;
typedef struct _s10 is_varsandstatements;
typedef struct _s14 p_statementlist;
typedef struct _s11 is_statement;
typedef struct _s21 is_expr;
typedef struct _s17 is_funcinvocation;

// Id token
typedef struct _28
{
    char *id;
    int line;
    int column;
} id_token;

// Statement List Block (from Statement)
typedef struct _s27
{
    is_statement *u_stat;
    struct _s27 *next;
} p_bstatementlist;

// Expression Only
typedef struct _26
{
    is_expr *u_expr;
} is_expr1;

// Expression FuncInvocation
typedef struct _25
{
    is_funcinvocation *u_funcinvocation;
} is_expr_funcinvocation;

// Literal
typedef struct _s24
{
    char *id;
    id_token *value;
} is_literal;

// Signal Expr
typedef struct _s23
{
    id_token *signal;
    is_expr *u_expr;
} is_signal;

// Operator
typedef struct _s22
{
    is_expr *u_expr_left;
    id_token *operator;
    is_expr *u_expr_right;
} is_oper;

typedef enum
{
    d_oper,
    d_signal,
    d_literal,
    d_expr_funcinvocation,
    d_expr1
} disc_exp;

// Expr
typedef struct _s21
{
    disc_exp disc_d;
    union
    {
        is_oper *u_oper;
        is_signal *u_signal;
        is_literal *u_literal;
        is_expr_funcinvocation *u_funcinvocation;
        is_expr1 *u_expr1;
    } expr;
} is_expr;

// Expr List
typedef struct _s20
{
    is_expr *u_expr;
    struct _s20 *next;
} is_exprlist;

// Print (from Statement)
typedef struct _s19
{
    id_token *print;
    id_token *value;
    is_expr *u_expr;
} p_print;

// Parse Args
typedef struct _s18
{
    id_token *id;
    is_expr *u_expr;
    id_token *parse;
} is_parseargs;

// Func Invocation
typedef struct _s17
{
    id_token *id;
    is_exprlist *u_exprlist;
} is_funcinvocation;

// Return (from Statement)
typedef struct _s16
{
    id_token *id;
    is_expr *u_expr;
} p_return;

// For (from Statement)
typedef struct _s15
{
    id_token *id;
    is_expr *u_expr;
    p_statementlist *u_statlist;
} p_for;

// Statement List (from Statement)
typedef struct _s14
{
    is_statement *u_stat;
    struct _s14 *next;
} p_statementlist;

// If (from Statement)
typedef struct _s13
{
    id_token *id;
    is_expr *u_expr;
    p_statementlist *u_statlist;
    p_statementlist *u_statlistop;
} p_if;

// Id Expr (from Statment)
typedef struct _s12
{
    id_token *id;
    id_token *op;
    is_expr *u_expr;
} p_id_expr;

typedef enum
{
    d_idexpr,
    d_if,
    d_statlist,
    d_bstatlist,
    d_for,
    d_return,
    d_funcinvocation,
    d_parseargs,
    d_print
} disc_stat;

// Statement
typedef struct _s11
{
    disc_stat disc_d;
    union
    {
        p_id_expr *u_idexpr;
        p_if *u_if;
        p_statementlist *u_statlist;
        p_bstatementlist *u_bstatlist;
        p_for *u_for;
        p_return *u_return;
        is_funcinvocation *u_funcinvocation;
        is_parseargs *u_parseargs;
        p_print *u_print;
    } prod;
} is_statement;

// Vars and Statements
typedef struct _s10
{
    is_vardecl *u_vardec;
    is_statement *u_stat;
    is_varsandstatements *next;
} is_varsandstatements;

// Parameters List
typedef struct _s9
{
    id_token *id;
    char *u_type;
    struct _s9 *next;
} is_parameters_list;

// VarSpecList
typedef struct _s8
{
    id_token *id;
    char *u_type;
    struct _s8 *next;
} is_varspec_list;

// VarSpec
typedef struct _s7
{
    id_token *id;
    is_varspec_list *u_varspec_list;
} is_varspec;

// Function Body
typedef struct _s6
{
    is_varsandstatements *u_varsandstatements;
} is_funcbody;

// Parameters
typedef struct _s5
{
    id_token *id;
    char *u_type;
    is_parameters_list *u_plist;
} is_parameters;

// Functions Declaration
typedef struct _s4
{
    table_element *symtab;
    is_parameters *u_parameters;
    char *u_type;
    id_token *id;
    is_funcbody *u_funcbody;
} is_funcdecl;

// Variables Declaration
typedef struct _s3
{
    is_varspec *u_varspec;
} is_vardecl;

// Declarations
typedef struct _s2
{
    is_vardecl *u_vardecl;
    is_funcdecl *u_funcdecl;
    struct _s2 *next;
} is_declarations;

// Program
typedef struct _s1
{
    table_element *symtab;
    is_declarations *u_decl;
} is_program;

#endif
