/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

#ifndef LLVM_H
#define LLVM_H

// Prototypes
void program(is_program *p);
void declarations(table_element **symtab, is_declarations *is);
void funcdecl(table_element **symtab, is_funcdecl *is);
void paramdecl(table_element **symtab_func, table_element **symtab_vars, is_parameters *ip);
void vardecl(table_element **symtab, is_vardecl *is);
void function_header(table_element **symtab, is_parameters *ip);
void function_body(table_element **symtab, is_funcbody *ip);
void statement(table_element **symtab, is_statement *ip);
void llvm_idexpr(table_element **symtab, p_id_expr *pie);
void llvm_return(table_element **symtab, p_return *pr);
void funcinvocation(table_element **symtab, is_funcinvocation *ifi);
void parseargs(table_element **symtab, is_parseargs *ipa);
void llvm_print(table_element **symtab, p_print *pp);
void statementlist(table_element **symtab, p_statementlist *psl);
void bstatementlist(table_element **symtab, p_bstatementlist *pbsl);
void llvm_if(table_element **symtab, p_if *pt);
void llvm_for(table_element **symtab, p_for *pf);
void expr_list(table_element **symtab, is_exprlist *iel);
char *expr(table_element **symtab, is_expr *ie);
char *oper(table_element **symtab, is_oper *io);
char *signal(table_element **symtab, is_signal *is);
char *literal(table_element **symtab, is_literal *il);
char *expr_funcinvocation(table_element **symtab, is_expr_funcinvocation *iefi);
char *expr1(table_element **symtab, is_expr1 *ie1);

#endif
