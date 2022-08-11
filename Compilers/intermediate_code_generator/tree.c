/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

// Libraries
#include "structures.h"
#include "tree.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// Global Variables
int dots = 0;
bool annotated;
table_element *globalSymtab;
table_element *symtab;

/************************** Insert token **************************/

id_token *insert_token(char *id, int line, int column)
{
    id_token *it = (id_token *)malloc(sizeof(id_token));

    it->id = (char *)strdup(id);
    it->line = line;
    it->column = column;

    return it;
}

/**************************  Insert Functions  **************************/

// Program
is_program *insert_program(is_declarations *id)
{
    is_program *ip = (is_program *)malloc(sizeof(is_program));

    ip->u_decl = id;

    return ip;
}

// Declarations
is_declarations *insert_declarations(is_declarations *head, is_vardecl *ivd, is_funcdecl *ifd)
{
    is_declarations *aux = (is_declarations *)malloc(sizeof(is_declarations));

    aux->u_vardecl = ivd;
    aux->u_funcdecl = ifd;
    aux->next = NULL;

    if (!head)
        return aux;

    aux->next = head;
    return aux;
}

// Variables Declaration
is_vardecl *insert_variable_declaration(is_varspec *ivs)
{
    is_vardecl *ivd = (is_vardecl *)malloc(sizeof(is_vardecl));

    ivd->u_varspec = ivs;

    return ivd;
}

// VarSpec
is_varspec *insert_varspec(is_varspec_list *ivslist, id_token *id)
{
    is_varspec *ivs = (is_varspec *)malloc(sizeof(is_varspec));

    ivs->id = id;
    ivs->u_varspec_list = ivslist;

    return ivs;
}

// VarSpecList
is_varspec_list *insert_varspec_list(is_varspec_list *head, id_token *it, char *type)
{
    is_varspec_list *ivslist = (is_varspec_list *)malloc(sizeof(is_varspec_list));

    ivslist->id = it;
    ivslist->u_type = type;

    ivslist->next = NULL;

    if (!head)
        return ivslist;

    ivslist->next = head;
    return ivslist;
}

// Functions Declaration
is_funcdecl *insert_function_declaration(is_parameters *ip, char *type, id_token *str, is_funcbody *ifb)
{
    is_funcdecl *ifd = (is_funcdecl *)malloc(sizeof(is_funcdecl));

    ifd->u_parameters = ip;
    if (!type)
        ifd->u_type = type;
    else
        ifd->u_type = (char *)strdup(type);
    ifd->id = str;
    ifd->u_funcbody = ifb;

    return ifd;
}

// Type
char *insert_type(char *type)
{
    char *it = (char *)malloc(sizeof(char));

    it = (char *)strdup(type);

    return it;
}

// Parameters
is_parameters *insert_parameters(is_parameters_list *next, id_token *id, char *type)
{
    is_parameters *ip = (is_parameters *)malloc(sizeof(is_parameters));

    ip->id = id;
    ip->u_type = (char *)strdup(type);
    ip->u_plist = next;

    return ip;
}

// Parameters List
is_parameters_list *insert_parameters_list(is_parameters_list *head, id_token *id, char *type)
{
    is_parameters_list *ipl = (is_parameters_list *)malloc(sizeof(is_parameters_list));

    ipl->id = id;
    ipl->u_type = (char *)strdup(type);
    ipl->next = NULL;

    if (!head)
        return ipl;

    ipl->next = head;
    return ipl;
}

// Func Body
is_funcbody *insert_funcbody(is_varsandstatements *ivas)
{
    is_funcbody *ifb = (is_funcbody *)malloc(sizeof(is_funcbody));

    ifb->u_varsandstatements = ivas;

    return ifb;
}

// Vars and Statements
is_varsandstatements *insert_varsandstatements(is_varsandstatements *head, is_vardecl *ivd, is_statement *is)
{
    is_varsandstatements *ivas = (is_varsandstatements *)malloc(sizeof(is_varsandstatements));
    is_varsandstatements *tmp;

    ivas->u_vardec = ivd;
    ivas->u_stat = is;
    ivas->next = NULL;

    if (!head)
        return ivas;

    // Verificar se isto está bem
    for (tmp = head; tmp->next; tmp = tmp->next)
        ;
    tmp->next = ivas;

    return head;
}

// Assign
is_statement *insert_idexpr(id_token *op, id_token *id, is_expr *ie)
{
    is_statement *is = (is_statement *)malloc(sizeof(is_statement));
    p_id_expr *pie = (p_id_expr *)malloc(sizeof(p_id_expr));

    pie->op = op;
    pie->id = id;
    pie->u_expr = ie;

    is->disc_d = d_idexpr;
    is->prod.u_idexpr = pie;

    return is;
}

// Return
is_statement *insert_return(id_token *id, is_expr *ie)
{
    is_statement *is = (is_statement *)malloc(sizeof(is_statement));
    p_return *pr = (p_return *)malloc(sizeof(p_return));

    pr->u_expr = ie;
    pr->id = id;

    is->disc_d = d_return;
    is->prod.u_return = pr;

    return is;
}

// Statement -> FuncInvocation
is_statement *insert_pfuncinvocation(is_funcinvocation *ifi)
{
    is_statement *is = (is_statement *)malloc(sizeof(is_statement));

    is->disc_d = d_funcinvocation;
    is->prod.u_funcinvocation = ifi;

    return is;
}

// Statement -> ParseArgs
is_statement *insert_pparseargs(is_parseargs *ipa)
{
    is_statement *is = (is_statement *)malloc(sizeof(is_statement));

    is->disc_d = d_parseargs;
    is->prod.u_parseargs = ipa;

    return is;
}

// Print
is_statement *insert_print(id_token *print, is_expr *ie, id_token *value)
{
    is_statement *is = (is_statement *)malloc(sizeof(is_statement));
    p_print *pp = (p_print *)malloc(sizeof(p_print));

    pp->print = print;

    pp->u_expr = ie;
    pp->value = value;

    is->disc_d = d_print;
    is->prod.u_print = pp;

    return is;
}

// Statement -> StatementList
is_statement *insert_pstatementlist(p_bstatementlist *psl)
{
    is_statement *is = (is_statement *)malloc(sizeof(is_statement));

    is->disc_d = d_bstatlist;
    is->prod.u_bstatlist = psl;

    return is;
}

// If
is_statement *insert_if(id_token *id, is_expr *ie, p_statementlist *psl1, p_statementlist *psl2)
{
    is_statement *is = (is_statement *)malloc(sizeof(is_statement));
    p_if *pi = (p_if *)malloc(sizeof(p_if));

    pi->id = id;
    pi->u_expr = ie;
    pi->u_statlist = psl1;
    pi->u_statlistop = psl2;

    is->disc_d = d_if;
    is->prod.u_if = pi;

    return is;
}

// For
is_statement *insert_for(id_token *id, is_expr *ie, p_statementlist *psl)
{
    is_statement *is = (is_statement *)malloc(sizeof(is_statement));
    p_for *pf = (p_for *)malloc(sizeof(p_for));

    pf->id = id;
    pf->u_expr = ie;
    pf->u_statlist = psl;

    is->disc_d = d_for;
    is->prod.u_for = pf;

    return is;
}

// StatementList
p_statementlist *insert_statementlist(p_statementlist *head, is_statement *is)
{
    p_statementlist *psl = (p_statementlist *)malloc(sizeof(p_statementlist));

    psl->u_stat = is;
    psl->next = head;

    return psl;
}

// Block StatementList
p_bstatementlist *insert_bstatementlist(p_bstatementlist *head, is_statement *is)
{
    p_bstatementlist *psl = (p_bstatementlist *)malloc(sizeof(p_bstatementlist));

    psl->u_stat = is;
    psl->next = head;

    return psl;
}

// ParseArgs
is_parseargs *insert_parseargs(id_token *id, is_expr *ie, id_token *parse)
{
    is_parseargs *ipa = (is_parseargs *)malloc(sizeof(is_parseargs));

    ipa->id = id;
    ipa->u_expr = ie;
    ipa->parse = parse;

    return ipa;
}

// FuncInvocation
is_funcinvocation *insert_funcinvocation(id_token *id, is_exprlist *iel)
{
    is_funcinvocation *ifi = (is_funcinvocation *)malloc(sizeof(is_funcinvocation));

    ifi->id = id;
    ifi->u_exprlist = iel;

    return ifi;
}

// ExprList
is_exprlist *insert_exprlist(is_exprlist *head, is_expr *expr)
{
    is_exprlist *iel = (is_exprlist *)malloc(sizeof(is_exprlist));
    is_exprlist *tmp;

    iel->u_expr = expr;
    iel->next = NULL;

    if (!head)
        return iel;

    for (tmp = head; tmp->next; tmp = tmp->next)
        ;
    tmp->next = iel;

    return head;
}

// Expr operator
is_expr *insert_expr_operator(is_expr *iel, id_token *operator, is_expr * ier)
{
    is_expr *ie = (is_expr *)malloc(sizeof(is_expr));
    is_oper *io = (is_oper *)malloc(sizeof(is_oper));

    io->u_expr_left = iel;
    io->operator= operator;
    io->u_expr_right = ier;

    ie->disc_d = d_oper;
    ie->expr.u_oper = io;

    return ie;
}

// Expr Signal
is_expr *insert_expr_signal(is_expr *iexpr, id_token *signal)
{
    is_expr *ie = (is_expr *)malloc(sizeof(is_expr));
    is_signal *is = (is_signal *)malloc(sizeof(is_signal));

    is->u_expr = iexpr;
    is->signal = signal;

    ie->disc_d = d_signal;
    ie->expr.u_signal = is;

    return ie;
}

// Expr Literal
is_expr *insert_expr_literal(char *id, id_token *value)
{
    is_expr *ie = (is_expr *)malloc(sizeof(is_expr));
    is_literal *il = (is_literal *)malloc(sizeof(is_literal));

    il->id = (char *)strdup(id);
    il->value = value;

    ie->disc_d = d_literal;
    ie->expr.u_literal = il;

    return ie;
}

// Expr FuncInvocation
is_expr *insert_expr_funcinvocation(is_funcinvocation *ifc)
{
    is_expr *ie = (is_expr *)malloc(sizeof(is_expr));
    is_expr_funcinvocation *iefi = (is_expr_funcinvocation *)malloc(sizeof(is_expr_funcinvocation));

    iefi->u_funcinvocation = ifc;

    ie->disc_d = d_expr_funcinvocation;
    ie->expr.u_funcinvocation = iefi;

    return ie;
}

// Expr1
is_expr *insert_expr1(is_expr *iexpr)
{
    is_expr *ie = (is_expr *)malloc(sizeof(is_expr));
    is_expr1 *ie1 = (is_expr1 *)malloc(sizeof(is_expr1));

    ie1->u_expr = iexpr;

    ie->disc_d = d_expr1;
    ie->expr.u_expr1 = ie1;

    return ie;
}

/**************************  Print functions  **************************/

// Program
void print_program(is_program *ip, bool is_annotated)
{
    annotated = is_annotated;
    globalSymtab = ip->symtab;

    if (ip == NULL)
        return;

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("Program\n");
    dots++;
    print_declarations(ip->u_decl);
    dots--;
}

// Declarations
void print_declarations(is_declarations *id)
{
    if (id == NULL)
        return;

    for (; id != NULL; id = id->next)
    {
        // DEBUG
        // printf("Declarations\n");
        print_var_declaration(id->u_vardecl);
        print_function_declaration(id->u_funcdecl);
    }
}

// Variables Declaration
void print_var_declaration(is_vardecl *ivd)
{
    if (ivd == NULL)
        return;

    print_varspec(ivd->u_varspec);
}

// Functions Declaration
void print_function_declaration(is_funcdecl *fd)
{
    if (fd == NULL)
        return;

    symtab = fd->symtab;

    for (int i = 0; i < dots; i++)
        printf("..");
    // DEBUG
    printf("FuncDecl\n");

    dots++;
    print_function_header(fd->u_parameters, fd->u_type, fd->id);
    print_function_body(fd->u_funcbody);
    dots--;
}

// VarSpec
void print_varspec(is_varspec *ivs)
{
    if (ivs == NULL)
        return;

    is_varspec_list *ivslist = ivs->u_varspec_list;
    char *u_type;
    for (; ivslist != NULL; ivslist = ivslist->next)
    {
        if (ivslist->u_type != NULL)
            u_type = ivslist->u_type;
    }

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("VarDecl\n");
    dots++;
    for (int i = 0; i < dots; i++)
        printf("..");
    print_type(u_type);
    for (int i = 0; i < dots; i++)
        printf("..");
    printf("Id(%s)\n", ivs->id->id);
    dots--;
    print_varspec_list(ivs->u_varspec_list, u_type);
}

// VarSpecList
void print_varspec_list(is_varspec_list *ivslist, char *u_type)
{
    if (ivslist == NULL)
        return;

    for (; ivslist != NULL; ivslist = ivslist->next)
    {
        if (ivslist->u_type == NULL)
        {
            for (int i = 0; i < dots; i++)
                printf("..");
            printf("VarDecl\n");
            dots++;
            for (int i = 0; i < dots; i++)
                printf("..");
            print_type(u_type);
            for (int i = 0; i < dots; i++)
                printf("..");
            printf("Id(%s)\n", ivslist->id->id);
            dots--;
        }
    }
}

// Function Header
void print_function_header(is_parameters *ip, char *it, id_token *id)
{
    for (int i = 0; i < dots; i++)
        printf("..");
    printf("FuncHeader\n");

    dots++;

    for (int i = 0; i < dots; i++)
        printf("..");
    if (id != NULL)
        printf("Id(%s)\n", id->id);
    if (it != NULL)
        for (int i = 0; i < dots; i++)
            printf("..");
    print_type(it);
    print_parameters(ip);

    dots--;
}

// Function Body
void print_function_body(is_funcbody *ifb)
{
    if (ifb == NULL)
        return;

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("FuncBody\n");

    dots++;
    print_varsandstatements(ifb->u_varsandstatements);
    dots--;
}

// Parameters
void print_parameters(is_parameters *ip)
{
    for (int i = 0; i < dots; i++)
        printf("..");
    printf("FuncParams\n");

    if (ip == NULL)
        return;

    dots++;

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("ParamDecl\n");

    dots++;

    for (int i = 0; i < dots; i++)
        printf("..");
    print_type(ip->u_type);

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("Id(%s)\n", ip->id->id);

    // Print Parameters list
    for (; ip->u_plist != NULL; ip->u_plist = ip->u_plist->next)
    {
        dots--;

        for (int i = 0; i < dots; i++)
            printf("..");
        printf("ParamDecl\n");

        dots++;
        for (int i = 0; i < dots; i++)
            printf("..");
        print_type(ip->u_plist->u_type);
        for (int i = 0; i < dots; i++)
            printf("..");
        printf("Id(%s)\n", ip->u_plist->id->id);
    }

    dots -= 2;
}

// Type
void print_type(char *it)
{
    if (it == NULL)
        return;

    char type[8];
    strcpy(type, it);
    type[0] = toupper(type[0]);

    printf("%s\n", type);
}

// Vars and Statements
void print_varsandstatements(is_varsandstatements *ivas)
{
    if (ivas == NULL)
        return;

    for (; ivas->next != NULL; ivas = ivas->next)
    {
        print_var_declaration(ivas->u_vardec);
        print_statement(ivas->u_stat);
    }

    print_var_declaration(ivas->u_vardec);
    print_statement(ivas->u_stat);
}

// Statement
void print_statement(is_statement *is)
{
    if (is == NULL)
        return;

    switch (is->disc_d)
    {
    case d_idexpr:
        print_idexpr(is->prod.u_idexpr);
        break;

    case d_return:
        print_return(is->prod.u_return);
        break;

    case d_funcinvocation:
        print_funcinvocation(is->prod.u_funcinvocation);
        break;

    case d_parseargs:
        print_parseargs(is->prod.u_parseargs);
        break;

    case d_print:
        print_print(is->prod.u_print);
        break;

    case d_statlist:
        print_statementlist(is->prod.u_statlist);
        break;

    case d_bstatlist:
        print_bstatementlist(is->prod.u_bstatlist);
        break;

    case d_if:
        print_if(is->prod.u_if);
        break;

    case d_for:
        print_for(is->prod.u_for);
        break;

    default:
        break;
    }
}

// Assign
void print_idexpr(p_id_expr *pie)
{
    if (pie == NULL)
        return;

    table_element *token;

    for (int i = 0; i < dots; i++)
        printf("..");

    if (annotated)
    {
        token = search_id(symtab, pie->id->id, false);
        if (token == NULL)
            token = search_id(globalSymtab, pie->id->id, false);
        else 
        {
            if (token->id->line > pie->id->line)
                token = search_id(globalSymtab, pie->id->id, false);
        }
        printf("Assign - ");
        print_annotated_type(token->id->type);
    }
    else
        printf("Assign\n");

    dots++;
    for (int i = 0; i < dots; i++)
        printf("..");

    if (annotated)
    {
        printf("Id(%s) - ", token->id->id);
        print_annotated_type(token->id->type);
    }
    else
        printf("Id(%s)\n", pie->id->id);

    print_expr(pie->u_expr);
    dots--;
}

// Return
void print_return(p_return *pr)
{
    if (pr == NULL)
        return;

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("Return\n");

    dots++;
    print_expr(pr->u_expr);
    dots--;
}

// FuncInvocation
void print_funcinvocation(is_funcinvocation *ifi)
{
    if (ifi == NULL)
        return;

    for (int i = 0; i < dots; i++)
        printf("..");

    table_element *token;

    if (annotated)
    {
        token = search_funcdecl(globalSymtab, ifi->id->id);
        if (token->funcdec->type && strcmp(token->funcdec->type, "none"))
        {
            printf("Call - ");
            print_annotated_type(token->funcdec->type);
        }
        else
            printf("Call\n");
    }
    else
        printf("Call\n");

    dots++;
    for (int i = 0; i < dots; i++)
        printf("..");

    if (annotated)
    {
        printf("Id(%s) - (", token->funcdec->id);
        print_params(token->funcdec->params);
        printf(")\n");
    }
    else
        printf("Id(%s)\n", ifi->id->id);

    print_exprlist(ifi->u_exprlist);
    dots--;
}

// ParseArgs
void print_parseargs(is_parseargs *ipa)
{
    if (ipa == NULL)
        return;
    for (int i = 0; i < dots; i++)
        printf("..");

    table_element *token;
    if (annotated)
    {
        token = search_id(symtab, ipa->id->id, false);
        if (token == NULL)
            token = search_id(globalSymtab, ipa->id->id, false);
        printf("ParseArgs - ");
        print_annotated_type(token->id->type);
    }
    else
        printf("ParseArgs\n");

    dots++;
    for (int i = 0; i < dots; i++)
        printf("..");

    if (annotated)
    {
        printf("Id(%s) - ", token->id->id);
        print_annotated_type(token->id->type);
    }
    else
        printf("Id(%s)\n", ipa->id->id);

    print_expr(ipa->u_expr);
    dots--;
}

// StatementList
void print_statementlist(p_statementlist *psl)
{
    if (psl == NULL)
        return;

    for (; psl != NULL; psl = psl->next)
    {
        print_statement(psl->u_stat);
    }
}

// Block StatementList
void print_bstatementlist(p_bstatementlist *psl)
{
    if (psl == NULL)
        return;

    // Verificar se temos de dar print a block
    // Temos de percorrer a lista toda e verificar que as produções statement não estão vazias
    p_bstatementlist *tmp;
    tmp = psl;
    int a = 0;
    for (; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->u_stat != NULL && tmp->u_stat->disc_d != d_bstatlist)
            a++;
        // if (tmp->u_stat->disc_d == d_bstatlist && tmp->u_stat->prod.u_bstatlist == NULL) a--;
        if (tmp->u_stat != NULL && tmp->u_stat->disc_d == d_bstatlist && tmp->u_stat->prod.u_bstatlist != NULL)
        {
            p_bstatementlist *aux;
            int b = 0;
            for (aux = tmp->u_stat->prod.u_bstatlist; aux != NULL; aux = aux->u_stat->prod.u_bstatlist)
            {
                if (aux->u_stat != NULL && aux->u_stat->disc_d != d_bstatlist)
                {
                    b = 1;
                    break;
                }
                if (aux->u_stat == NULL)
                    break;
            }
            a += b;
        }
    }

    if (a >= 2)
    {
        for (int i = 0; i < dots; i++)
            printf("..");
        printf("Block\n");

        dots++;

        for (; psl != NULL; psl = psl->next)
        {
            print_statement(psl->u_stat);
        }

        dots--;
    }
    else
        for (; psl != NULL; psl = psl->next)
        {
            print_statement(psl->u_stat);
        }
}

// Print
void print_print(p_print *pp)
{
    if (pp == NULL)
        return;

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("Print\n");

    dots++;
    if (pp->value == NULL)
    {
        print_expr(pp->u_expr);
    }
    else
    {
        for (int i = 0; i < dots; i++)
            printf("..");
        printf("StrLit(%s)\n", pp->value->id);
    }
    dots--;
}

// If
void print_if(p_if *pi)
{
    if (pi == NULL)
        return;

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("If\n");

    dots++;
    print_expr(pi->u_expr);

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("Block\n");

    dots++;
    print_statementlist(pi->u_statlist);
    dots--;

    for (int i = 0; i < dots; i++)
        printf("..");
    printf("Block\n");

    dots++;
    print_statementlist(pi->u_statlistop);
    dots--;
    dots--;
}

// For
void print_for(p_for *pf)
{
    if (pf == NULL)
        return;
    for (int i = 0; i < dots; i++)
        printf("..");
    printf("For\n");

    dots++;
    print_expr(pf->u_expr);
    for (int i = 0; i < dots; i++)
        printf("..");
    printf("Block\n");

    dots++;
    print_statementlist(pf->u_statlist);
    dots--;
    dots--;
}

// ExprList
void print_exprlist(is_exprlist *iel)
{
    if (iel == NULL)
        return;

    for (; iel != NULL; iel = iel->next)
        print_expr(iel->u_expr);
}

// Expr
void print_expr(is_expr *ie)
{
    if (ie == NULL)
        return;

    switch (ie->disc_d)
    {
    case d_oper:
        print_oper(ie->expr.u_oper);
        break;

    case d_signal:
        print_signal(ie->expr.u_signal);
        break;

    case d_literal:
        print_literal(ie->expr.u_literal);
        break;

    case d_expr_funcinvocation:
        print_expr_funcinvocation(ie->expr.u_funcinvocation);
        break;

    case d_expr1:
        print_expr1(ie->expr.u_expr1);
        break;

    default:
        break;
    }
}

// Operator
void print_oper(is_oper *io)
{
    if (io == NULL)
        return;
    for (int i = 0; i < dots; i++)
        printf("..");

    if (annotated)
    {
        if (!strcmp(io->operator->id, "Plus") || !strcmp(io->operator->id, "Minus") || !strcmp(io->operator->id, "Mul") || !strcmp(io->operator->id, "Div") || !strcmp(io->operator->id, "Mod"))
        {
            is_expr *search = io->u_expr_left;
            char *type = NULL;
            if (!strcmp(io->operator->id, "Minus"))
                io->operator->id =(char *) strdup("Sub");
            if (!strcmp(io->operator->id, "Plus"))
                io->operator->id =(char *) strdup("Add");

            while (1)
            {
                switch (search->disc_d)
                {
                case d_oper:
                    search = search->expr.u_oper->u_expr_left;
                    break;

                case d_signal:
                    search = search->expr.u_signal->u_expr;
                    break;

                case d_literal:
                {
                    is_literal *token_search = search->expr.u_literal;
                    if (!strcmp(token_search->id, "Id"))
                    {
                        table_element *token = search_id(symtab, token_search->value->id, false);
                        if (token == NULL)
                            token = search_id(globalSymtab, token_search->value->id, false);
                        type = token->id->type;
                    }
                    else if (!strcmp(token_search->id, "IntLit"))
                        type = "int";
                    else if (!strcmp(token_search->id, "RealLit"))
                        type = "float32";
                    break;
                }
                case d_expr_funcinvocation:
                {
                    is_funcinvocation *func_search = search->expr.u_funcinvocation->u_funcinvocation;
                    table_element *token = search_funcdecl(globalSymtab, func_search->id->id);
                    type = token->funcdec->type;
                    break;
                }
                case d_expr1:
                    search = search->expr.u_expr1->u_expr;
                    break;
                }
                if (type)
                {
                    printf("%s - ", io->operator->id);
                    print_annotated_type(type);
                    break;
                }
            }
        }
        else
            printf("%s - bool\n", io->operator->id);
    }
    else
    {
        if (!strcmp(io->operator->id, "Minus"))
            io->operator->id =(char *) strdup("Sub");
        if (!strcmp(io->operator->id, "Plus"))
            io->operator->id =(char *) strdup("Add");
        printf("%s\n", io->operator->id);
    }

    dots++;
    print_expr(io->u_expr_left);
    print_expr(io->u_expr_right);
    dots--;
}

// Signal
void print_signal(is_signal *is)
{
    if (is == NULL)
        return;
    for (int i = 0; i < dots; i++)
        printf("..");
    if (annotated)
    {
        is_expr *search = is->u_expr;
        char *type = NULL;
        while (1)
        {
            switch (search->disc_d)
            {
            case d_oper:
                search = search->expr.u_oper->u_expr_left;
                break;

            case d_signal:
                search = search->expr.u_signal->u_expr;
                break;

            case d_literal:
            {
                is_literal *token_search = search->expr.u_literal;
                if (!strcmp(token_search->id, "Id"))
                {
                    table_element *token = search_id(symtab, token_search->value->id, false);
                    if (token == NULL)
                        token = search_id(globalSymtab, token_search->value->id, false);
                    type = token->id->type;
                }
                else if (!strcmp(token_search->id, "IntLit"))
                    type = "int";
                else if (!strcmp(token_search->id, "RealLit"))
                    type = "float32";
                break;
            }
            case d_expr_funcinvocation:
            {
                is_funcinvocation *func_search = search->expr.u_funcinvocation->u_funcinvocation;
                table_element *token = search_funcdecl(globalSymtab, func_search->id->id);
                type = token->funcdec->type;
                break;
            }
            case d_expr1:
                search = search->expr.u_expr1->u_expr;
                break;
            }
            if (type)
            {
                printf("%s - ", is->signal->id);
                print_annotated_type(type);
                break;
            }
        }
    }
    else
        printf("%s\n", is->signal->id);

    /*for (int i = 0; i < dots + 1; i++)
        printf("..");*/

    dots++;
    print_expr(is->u_expr);
    dots--;
}

// Literal
void print_literal(is_literal *il)
{
    if (il == NULL)
        return;

    for (int i = 0; i < dots; i++)
        printf("..");

    if (annotated)
    {
        if (!strcmp(il->id, "Id"))
        {
            table_element *token = search_id(symtab, il->value->id, false);
            if (token == NULL)
                token = search_id(globalSymtab, il->value->id, false);
            printf("Id(%s) - ", token->id->id);
            print_annotated_type(token->id->type);
        }
        else if (!strcmp(il->id, "IntLit"))
            printf("IntLit(%s) - int\n", il->value->id);
        else if (!strcmp(il->id, "RealLit"))
            printf("RealLit(%s) - float32\n", il->value->id);
    }
    else
        printf("%s(%s)\n", il->id, il->value->id);
}

// FuncInvocation
void print_expr_funcinvocation(is_expr_funcinvocation *ifi)
{
    if (ifi == NULL)
        return;
    print_funcinvocation(ifi->u_funcinvocation);
}

// Expr1
void print_expr1(is_expr1 *ie1)
{
    if (ie1 == NULL)
        return;

    print_expr(ie1->u_expr);
}

void print_annotated_type(char *it)
{
    if (it == NULL)
        return;

    char type[8];
    strcpy(type, it);
    type[0] = tolower(type[0]);

    printf("%s\n", type);
}
