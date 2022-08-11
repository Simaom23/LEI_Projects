/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

// Libraries
#include "structures.h"
#include "symbol_table.h"

// Check Functions
int check_program(is_program *ip);
int check_declarations(table_element **symtab, is_declarations *id);
int check_vardecl(table_element **symtab, is_vardecl *ivd);
int check_funcdecl(table_element **symtab, is_funcdecl *ifd);
int check_varspec(table_element **symtab, is_varspec *ivs);
int check_funcbody(table_element **symtab, is_funcbody *ifb);
int check_varsandstatements(table_element **symtab, is_varsandstatements *ivs);
int check_statement(table_element **symtab, is_statement *is);
int check_id_expr(table_element **symtab, p_id_expr *pie);
int check_if(table_element **symtab, p_if *pi);
int check_statementlist(table_element **symtab, p_statementlist *psl);
int check_bstatementlist(table_element **symtab, p_bstatementlist *pslb);
int check_for(table_element **symtab, p_for *pf);
int check_return(table_element **symtab, p_return *pr);
int check_funcinvocation(table_element **symtab, is_funcinvocation *ifi);
int check_parseargs(table_element **symtab, is_parseargs *ipa);
int check_print(table_element **symtab, p_print *p);
const char* check_expr(table_element **symtab, is_expr *ie);
const char* check_oper(table_element **symtab, is_oper *io);
const char* check_error_oper(is_oper *io, const char *type1, const char *type2, char *op);
const char* check_signal(table_element **symtab, is_signal *is);
const char* check_literal(table_element **symtab, is_literal *il);
const char* check_expr_funcinvocation(table_element **symtab, is_expr_funcinvocation *iefi);
const char* check_expr1(table_element **symtab, is_expr1 *ie1);
int check_params(table_element **symtab, is_funcinvocation *ifi);

void print_function_error(table_element **symtab, is_funcinvocation *ifi);
void print_function_error_undef(table_element **symtab,is_funcinvocation *ifi);
