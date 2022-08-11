/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

// Libraries
#include "structures.h"

// Insert Functions
id_token *insert_token(char *id, int line, int column);
is_program *insert_program(is_declarations *id);
is_declarations *insert_declarations(is_declarations *head, is_vardecl *ivd, is_funcdecl *ifd);
is_funcdecl *insert_function_declaration(is_parameters *ip, char *type, id_token *id, is_funcbody *ifb);
is_vardecl *insert_variable_declaration(is_varspec *ivs);
is_varspec *insert_varspec(is_varspec_list *ivsl, id_token *id);
is_varspec_list *insert_varspec_list(is_varspec_list *head, id_token *it, char *type);
char *insert_type(char *type);
is_parameters *insert_parameters(is_parameters_list *head, id_token *id, char *type);
is_parameters_list *insert_parameters_list(is_parameters_list *head, id_token *id, char *type);
is_funcbody *insert_funcbody(is_varsandstatements *ivas);
is_varsandstatements *insert_varsandstatements(is_varsandstatements *head, is_vardecl *ivd, is_statement *is);
is_statement *insert_idexpr(id_token *op, id_token *id, is_expr *ie);
is_statement *insert_return(id_token *id, is_expr *ie);
is_statement *insert_pfuncinvocation(is_funcinvocation *ifi);
is_statement *insert_pparseargs(is_parseargs *ipa);
is_statement *insert_pstatementlist(p_bstatementlist *psl);
is_statement *insert_print(id_token *print, is_expr *ie, id_token *value);
is_statement *insert_if(id_token *id, is_expr *ie, p_statementlist *psl1, p_statementlist *psl2);
is_statement *insert_for(id_token *id, is_expr *ie, p_statementlist *psl);
p_statementlist *insert_statementlist(p_statementlist *head, is_statement *is);
p_bstatementlist *insert_bstatementlist(p_bstatementlist *head, is_statement *is);
is_parseargs *insert_parseargs(id_token *id, is_expr *ie, id_token *parse);
is_funcinvocation *insert_funcinvocation(id_token *id, is_exprlist *iel);
is_exprlist *insert_exprlist(is_exprlist *head, is_expr *expr);
is_expr *insert_expr_operator(is_expr *iel, id_token *operator, is_expr * ier);
is_expr *insert_expr_signal(is_expr *iexpr, id_token *signal);
is_expr *insert_expr_literal(char *id, id_token *value);
is_expr *insert_expr_funcinvocation(is_funcinvocation *ifc);
is_expr *insert_expr1(is_expr *iexpr);

// Print functions
void print_program(is_program *ip, bool is_annotated);
void print_declarations(is_declarations *id);
void print_function_declaration(is_funcdecl *fd);
void print_varspec(is_varspec *ivs);
void print_varspec_list(is_varspec_list *ivslist, char *u_type);
void print_var_declaration(is_vardecl *ivd);
void print_parameters(is_parameters *ip);
void print_type(char *it);
void print_function_header(is_parameters *ip, char *it, id_token *id);
void print_function_body(is_funcbody *ifb);
void print_varsandstatements(is_varsandstatements *ivas);
void print_statement(is_statement *is);
void print_idexpr(p_id_expr *pie);
void print_expr(is_expr *ie);
void print_return(p_return *pr);
void print_funcinvocation(is_funcinvocation *ifi);
void print_parseargs(is_parseargs *ipa);
void print_statementlist(p_statementlist *psl);
void print_bstatementlist(p_bstatementlist *psl);
void print_print(p_print *pp);
void print_if(p_if *pi);
void print_for(p_for *pf);
void print_exprlist(is_exprlist *iel);
void print_expr(is_expr *ie);
void print_oper(is_oper *io);
void print_signal(is_signal *is);
void print_literal(is_literal *il);
void print_expr_funcinvocation(is_expr_funcinvocation *ifi);
void print_expr1(is_expr1 *ie1);
void print_annotated_type(char *type);
