/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

/* Definitions */
%{
    // Libraries
    #include <stdio.h>
    #include "structures.h"
    #include "tree.h"
    #include "y.tab.h"
    
    // Prototypes
    int yylex (void);
    void yyerror(char* s);

    // Global Variables
    extern int line, column;
    is_program* head = NULL;
%}

/* Rules */
// Tokens
%token SEMICOLON COMMA BLANKID LBRACE LPAR LSQ RBRACE RPAR RSQ PACKAGE ELSE VAR INT FLOAT32 BOOL STRING FUNC CMDARGS
%token RESERVED 
%token<token>ID STRLIT INTLIT REALLIT ASSIGN STAR DIV MINUS PLUS EQ GE GT LE LT MOD NE NOT AND OR FOR IF RETURN PARSEINT PRINT 

// Types
%type<ip>Program
%type<id>Declarations
%type<ivd>VarDeclaration
%type<ifd>FuncDeclaration
%type<p>Parameters
%type<ivs>VarSpec
%type<ivslist>VarSpecList
%type<t>Type
%type<ifb>FuncBody
%type<pl>ParametersList
%type<ivas>VarAndStatements
%type<is>Statement
%type<ie>Expr
%type<ifi>FuncInvocation
%type<ipa>ParseArgs
%type<isl>StatementList
%type<iel>ExprList
%type<ibsl>StatementList1

// Union
%union{
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
}

// Precedence
%left COMMA
%right ASSIGN
%left OR
%left AND
%left EQ NE LT LE GT GE
%left PLUS MINUS 
%left MOD DIV STAR
%right NOT

/* Subroutines */
%%
Program: PACKAGE ID SEMICOLON Declarations                                          {$$=head=insert_program($4);}                                                                               
    ;

Declarations:                                                                       {$$=NULL;}
    | VarDeclaration SEMICOLON Declarations                                         {$$=insert_declarations($3, $1, NULL);}
    | FuncDeclaration SEMICOLON Declarations                                        {$$=insert_declarations($3, NULL, $1);}
    ;

VarDeclaration: VAR VarSpec                                                         {$$=insert_variable_declaration($2);}
    | VAR LPAR VarSpec SEMICOLON RPAR                                               {$$=insert_variable_declaration($3);}
    ;

VarSpec: ID VarSpecList                                                             {$$=insert_varspec($2, $1);}
    ;

VarSpecList: COMMA ID VarSpecList                                                   {$$=insert_varspec_list($3, $2, NULL);}
    | Type                                                                          {$$=insert_varspec_list(NULL, NULL, $1);}
    ;

Type: INT                                                                           {$$=insert_type("Int");}                                                  
    | FLOAT32                                                                       {$$=insert_type("Float32");}  
    | BOOL                                                                          {$$=insert_type("Bool");}  
    | STRING                                                                        {$$=insert_type("String");}  
    ;

FuncDeclaration: FUNC ID LPAR RPAR FuncBody                                         {$$=insert_function_declaration(NULL, NULL, $2, $5);}
    | FUNC ID LPAR Parameters RPAR FuncBody                                         {$$=insert_function_declaration($4, NULL, $2, $6);}
    | FUNC ID LPAR RPAR Type FuncBody                                               {$$=insert_function_declaration(NULL, $5, $2, $6);}
    | FUNC ID LPAR Parameters RPAR Type FuncBody                                    {$$=insert_function_declaration($4, $6, $2, $7);}
    ;

Parameters: ID Type ParametersList                                                  {$$=insert_parameters($3, $1, $2);}
    ;

ParametersList:                                                                     {$$=NULL;}
    | COMMA ID Type ParametersList                                                  {$$=insert_parameters_list($4, $2, $3);}
    ;

FuncBody: LBRACE VarAndStatements RBRACE                                            {$$=insert_funcbody($2);}
    ;

VarAndStatements:                                                                   {$$=NULL;}
    | VarAndStatements SEMICOLON                                                    {$$=insert_varsandstatements($1, NULL, NULL);}
    | VarAndStatements VarDeclaration SEMICOLON                                     {$$=insert_varsandstatements($1, $2, NULL);}
    | VarAndStatements Statement SEMICOLON                                          {$$=insert_varsandstatements($1, NULL, $2);}
    ;

Statement: ID ASSIGN Expr                                                           {$$=insert_idexpr($2, $1, $3);}
    | LBRACE StatementList1 RBRACE                                                  {$$=insert_pstatementlist($2);}
    | IF Expr LBRACE StatementList RBRACE                                           {$$=insert_if($1, $2, $4, NULL);}
    | IF Expr LBRACE StatementList RBRACE ELSE LBRACE StatementList RBRACE          {$$=insert_if($1, $2, $4, $8);}
    | FOR LBRACE StatementList RBRACE                                               {$$=insert_for($1, NULL, $3);}
    | FOR Expr LBRACE StatementList RBRACE                                          {$$=insert_for($1, $2, $4);}
    | RETURN                                                                        {$$=insert_return($1, NULL);}
    | RETURN Expr                                                                   {$$=insert_return($1, $2);}
    | FuncInvocation                                                                {$$=insert_pfuncinvocation($1);}
    | ParseArgs                                                                     {$$=insert_pparseargs($1);}
    | PRINT LPAR Expr RPAR                                                          {$$=insert_print($1, $3, NULL);}
    | PRINT LPAR STRLIT RPAR                                                        {$$=insert_print($1, NULL, $3);}
    | error                                                                         {;}
    ;

StatementList:                                                                      {$$=NULL;}
    | Statement SEMICOLON StatementList                                             {$$=insert_statementlist($3, $1);}
    ;

StatementList1:                                                                     {$$=NULL;}
    | Statement SEMICOLON StatementList1                                            {$$=insert_bstatementlist($3, $1);}
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR          {$$=insert_parseargs($1, $9, $5);}
    | ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                              {;}
    ;

FuncInvocation: ID LPAR RPAR                                                        {$$=insert_funcinvocation($1, NULL);}
    | ID LPAR ExprList RPAR                                                         {$$=insert_funcinvocation($1, $3);}
    | ID LPAR error RPAR                                                            {;}
    ;

Expr: Expr OR Expr                                                                  {$$=insert_expr_operator($1, $2, $3);}
    | Expr AND Expr                                                                 {$$=insert_expr_operator($1, $2, $3);}
    | Expr LT Expr                                                                  {$$=insert_expr_operator($1, $2, $3);}
    | Expr GT Expr                                                                  {$$=insert_expr_operator($1, $2, $3);}
    | Expr EQ Expr                                                                  {$$=insert_expr_operator($1, $2, $3);}
    | Expr NE Expr                                                                  {$$=insert_expr_operator($1, $2, $3);}
    | Expr LE Expr                                                                  {$$=insert_expr_operator($1, $2, $3);}
    | Expr GE Expr                                                                  {$$=insert_expr_operator($1, $2, $3);}
    | Expr PLUS Expr                                                                {$$=insert_expr_operator($1, $2, $3);}
    | Expr MINUS Expr                                                               {$$=insert_expr_operator($1, $2, $3);}
    | Expr STAR Expr                                                                {$$=insert_expr_operator($1, $2, $3);}
    | Expr DIV Expr                                                                 {$$=insert_expr_operator($1, $2, $3);}
    | Expr MOD Expr                                                                 {$$=insert_expr_operator($1, $2, $3);}
    | NOT Expr                                                                      {$$=insert_expr_signal($2, $1);}
    | MINUS Expr %prec DIV                                                          {$$=insert_expr_signal($2, $1);}
    | PLUS Expr %prec DIV                                                           {$$=insert_expr_signal($2, $1);}
    | INTLIT                                                                        {$$=insert_expr_literal("IntLit", $1);}                                                                
    | REALLIT                                                                       {$$=insert_expr_literal("RealLit", $1);}                                                              
    | ID                                                                            {$$=insert_expr_literal("Id", $1);}                                                              
    | FuncInvocation                                                                {$$=insert_expr_funcinvocation($1);}
    | LPAR Expr RPAR                                                                {$$=insert_expr1($2);}
    | LPAR error RPAR                                                               {;}
    ;

ExprList: ExprList COMMA Expr                                                       {$$=insert_exprlist($1, $3);}
    | Expr                                                                          {$$=insert_exprlist(NULL, $1);}
    ;

%%
