/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

// Libraries
#include "semantics.h"
#include "structures.h"
#include "symbol_table.h"
#include <stdio.h>
#include <string.h>

table_element **global_symtab;
bool printError = false;
bool exprError = true;
char *id_function_type = NULL;

int check_program(is_program *p)
{
    int errorcount = 0;

    global_symtab = &p->symtab;
    check_declarations(&p->symtab, p->u_decl);

    printError = true;
    errorcount = check_declarations(&p->symtab, p->u_decl);

    return errorcount;
}

int check_declarations(table_element **symtab, is_declarations *id)
{
    int errorcount = 0;

    if (id == NULL)
        return errorcount;

    for (; id != NULL; id = id->next)
    {
        errorcount += check_funcdecl(symtab, id->u_funcdecl);
        errorcount += check_vardecl(symtab, id->u_vardecl);
    }
    return errorcount;
}

int check_vardecl(table_element **symtab, is_vardecl *ivd)
{
    int errorcount = 0;

    if (ivd == NULL)
        return errorcount;

    errorcount += check_varspec(symtab, ivd->u_varspec);
    return errorcount;
}

int check_funcdecl(table_element **symtab, is_funcdecl *ifd)
{
    int errorcount = 0;
    if (ifd == NULL)
        return errorcount;

    table_element *newel;

    if (printError)
    {
        newel = search_funcdecl(*symtab, ifd->id->id);
        if (newel)
        {
            if (!newel->funcdec->seen)
                newel->funcdec->seen = true;
            else
                newel = NULL;
        }
    }
    else
    {
        table_element *check = search_id(*global_symtab, ifd->id->id, false);
        if (!check)
            newel = insert_func(symtab, ifd->id->id, ifd->u_type);
        else
            newel = NULL;
    }

    if (newel == NULL)
    {
        errorcount++;
        if (printError)
            printf("Line %d, column %d: Symbol %s", ifd->id->line, ifd->id->column, ifd->id->id);

        table_element *fdec = search_funcdecl(*global_symtab, ifd->id->id);
        if (fdec)
        {
            if (fdec->funcdec->params)
                if (printError)
                    printf("(");
            print_params(fdec->funcdec->params);
            if (fdec->funcdec->params)
                if (printError)
                    printf(")");
        }
        if (printError)
            printf(" already defined\n");
        return errorcount;
    }
    // Colocar parâmetros na symtab da função
    else
    {
        is_parameters_list *tmp;
        table_element *param;
        table_element *id;
        if (ifd->u_parameters != NULL)
        {
            if (printError)
            {
                id = search_id(ifd->symtab, ifd->u_parameters->id->id, false);
                if (id)
                {
                    if (!id->id->seen)
                    {
                        param = id;
                        id->id->seen = true;
                    }
                    else
                        param = NULL;
                }
                else
                    param = NULL;
            }
            else
            {
                param = insert_id(&ifd->symtab, ifd->u_parameters->id->id, ifd->u_parameters->id->line, ifd->u_parameters->id->column, ifd->u_parameters->u_type, true);
                insert_params(newel->funcdec, ifd->u_parameters->id->id, ifd->u_parameters->u_type);
            }
        }
        else
        {
            if (ifd->u_type)
                id_function_type = (char *)strdup(ifd->u_type);
            else
                id_function_type = NULL;
            errorcount += check_funcbody(&ifd->symtab, ifd->u_funcbody);
            return errorcount;
        }

        for (tmp = ifd->u_parameters->u_plist; tmp != NULL; tmp = tmp->next)
        {

            if (printError)
            {
                id = search_id(ifd->symtab, tmp->id->id, false);
                if (id)
                {
                    if (!id->id->seen)
                    {
                        param = id;
                        id->id->seen = true;
                    }
                    else
                        param = NULL;
                }
                else
                    param = NULL;
            }
            else
            {
                param = insert_id(&ifd->symtab, tmp->id->id, tmp->id->line, tmp->id->column, tmp->u_type, true);
                insert_params(newel->funcdec, tmp->id->id, tmp->u_type);
            }

            if (param == NULL)
            {
                errorcount++;
                if (printError)
                    printf("Line %d, column %d: Symbol %s already defined\n", tmp->id->line, tmp->id->column, tmp->id->id);
            }
        }
    }

    if (ifd->u_type)
        id_function_type = (char *)strdup(ifd->u_type);
    else
        id_function_type = NULL;
    errorcount += check_funcbody(&ifd->symtab, ifd->u_funcbody);

    return errorcount;
}

int check_varspec(table_element **symtab, is_varspec *ivs)
{
    int errorcount = 0;

    if (ivs == NULL)
        return errorcount;

    is_varspec_list *tmp = ivs->u_varspec_list;
    char *u_type;
    for (; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->u_type != NULL)
            u_type = tmp->u_type;
    }

    table_element *newel;

    if (printError)
    {
        newel = search_id(*symtab, ivs->id->id, false);
        if (newel)
        {
            if (!newel->id->seen)
                newel->id->seen = true;
            else
                newel = NULL;
        }
    }
    else
    {
        table_element *check = search_funcdecl(*global_symtab, ivs->id->id);
        if (!check)
            newel = insert_id(symtab, ivs->id->id, ivs->id->line, ivs->id->column, u_type, false);
        else
            newel = NULL;
    }

    if (newel == NULL)
    {
        errorcount++;
        if (printError)
            printf("Line %d, column %d: Symbol %s already defined\n", ivs->id->line, ivs->id->column, ivs->id->id);
    }
    else if (!newel->id->used)
        if (printError && symtab != global_symtab)
            printf("Line %d, column %d: Symbol %s declared but never used\n", ivs->id->line, ivs->id->column, ivs->id->id);

    tmp = ivs->u_varspec_list;
    for (; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->u_type == NULL)
        {
            if (printError)
            {
                newel = search_id(*symtab, tmp->id->id, false);
                if (newel)
                {
                    if (!newel->id->seen)
                        newel->id->seen = true;
                    else
                        newel = NULL;
                }
            }
            else
            {
                table_element *check = search_funcdecl(*global_symtab, tmp->id->id);
                if (!check)
                    newel = insert_id(symtab, tmp->id->id, tmp->id->line, tmp->id->column, u_type, false);
                else
                    newel = NULL;
            }

            if (newel == NULL)
            {
                errorcount++;
                if (printError)
                    printf("Line %d, column %d: Symbol %s already defined\n", tmp->id->line, tmp->id->column, tmp->id->id);
            }
            else if (!newel->id->used)
                if (printError && symtab != global_symtab)
                    printf("Line %d, column %d: Symbol %s declared but never used\n", tmp->id->line, tmp->id->column, tmp->id->id);
        }
    }

    return errorcount;
}

int check_funcbody(table_element **symtab, is_funcbody *ifb)
{
    int errorcount = 0;

    if (ifb == NULL)
        return errorcount;

    errorcount += check_varsandstatements(symtab, ifb->u_varsandstatements);
    return errorcount;
}

int check_varsandstatements(table_element **symtab, is_varsandstatements *ivs)
{
    int errorcount = 0;

    if (ivs == NULL)
        return errorcount;

    is_varsandstatements *tmp;
    for (tmp = ivs; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->u_stat)
            errorcount += check_statement(symtab, tmp->u_stat);
        if (tmp->u_vardec)
            errorcount += check_vardecl(symtab, tmp->u_vardec);
    }

    return errorcount;
}

int check_statement(table_element **symtab, is_statement *is)
{
    int errorcount = 0;

    if (is == NULL)
        return errorcount;

    switch (is->disc_d)
    {
    case d_idexpr:
        errorcount += check_id_expr(symtab, is->prod.u_idexpr);
        break;

    case d_if:
        errorcount += check_if(symtab, is->prod.u_if);
        break;

    case d_statlist:
        errorcount += check_statementlist(symtab, is->prod.u_statlist);
        break;

    case d_bstatlist:
        errorcount += check_bstatementlist(symtab, is->prod.u_bstatlist);
        break;

    case d_for:
        errorcount += check_for(symtab, is->prod.u_for);
        break;

    case d_return:
        errorcount += check_return(symtab, is->prod.u_return);
        break;

    case d_funcinvocation:
        errorcount += check_funcinvocation(symtab, is->prod.u_funcinvocation);
        break;

    case d_parseargs:
        errorcount += check_parseargs(symtab, is->prod.u_parseargs);
        break;

    case d_print:
        errorcount += check_print(symtab, is->prod.u_print);
        break;

    default:
        break;
    }

    return errorcount;
}

// TODO: FIX Operator = cannot be applied to types
int check_id_expr(table_element **symtab, p_id_expr *pie)
{
    int errorcount = 0;
    exprError = true;

    if (pie == NULL)
        return errorcount;

    // Verificar se id já exite na symtab da função
    table_element *id = search_id(*symtab, pie->id->id, true);
    if (id == NULL)
    {
        // Verificar se id existe na symtab global
        id = search_id(*global_symtab, pie->id->id, true);
        if (id == NULL)
        {
            if (printError)
                printf("Line %d, column %d: Cannot find symbol %s\n", pie->id->line, pie->id->column, pie->id->id);
            errorcount++;
        }
    }
    else
    {
        if (pie->id->line < id->id->line)
        {
            // Temos de procurar na symtab global porque o id não está declarado localmente
            id = search_id(*global_symtab, pie->id->id, true);
            if (id == NULL)
            {
                if (printError)
                    printf("Line %d, column %d: Cannot find symbol %s\n", pie->id->line, pie->id->column, pie->id->id);
                errorcount++;
            }
        }
    }

    const char *type = check_expr(symtab, pie->u_expr);

    if (type == NULL && id != NULL && id->id->type != NULL)
    {
        errorcount++;
        if (printError && exprError)
            printf("Line %d, column %d: Operator = cannot be applied to types %s, undef\n", pie->op->line, pie->op->column, id->id->type);
        return errorcount;
    }
    if (id == NULL && type != NULL)
    {
        errorcount++;
        if (printError && exprError)
            printf("Line %d, column %d: Operator = cannot be applied to types undef, %s\n", pie->op->line, pie->op->column, type);
        return errorcount;
    }
    if (id == NULL && type == NULL)
    {
        errorcount++;
        if (printError && exprError)
            printf("Line %d, column %d: Operator = cannot be applied to types undef, undef\n", pie->op->line, pie->op->column);
        return errorcount;
    }
    if (strcmp(id->id->type, type) != 0)
    {
        errorcount++;
        if (printError && exprError)
            printf("Line %d, column %d: Operator = cannot be applied to types %s, %s\n", pie->op->line, pie->op->column, id->id->type, type);
        return errorcount;
    }

    exprError = true;
    return errorcount;
}

int check_if(table_element **symtab, p_if *pi)
{
    int errorcount = 0;

    if (pi == NULL)
        return errorcount;

    // O type da check_expr tem de ser bool
    const char *type = check_expr(symtab, pi->u_expr);

    if (type == NULL)
    {
        errorcount++;
    }
    if (type && strcmp(type, "bool") != 0)
    {
        errorcount++;
        if (printError)
            printf("Line %d, column %d: Incompatible type %s in if statement\n", pi->id->line, pi->id->column + 1, type);
    }
    errorcount += check_statementlist(symtab, pi->u_statlist);
    errorcount += check_statementlist(symtab, pi->u_statlistop);

    return errorcount;
}

int check_statementlist(table_element **symtab, p_statementlist *psl)
{
    int errorcount = 0;

    if (psl == NULL)
        return errorcount;

    p_statementlist *aux;
    for (aux = psl; aux; aux = aux->next)
    {
        errorcount += check_statement(symtab, aux->u_stat);
    }

    return errorcount;
}

int check_bstatementlist(table_element **symtab, p_bstatementlist *pslb)
{
    int errorcount = 0;

    if (pslb == NULL)
        return errorcount;

    p_bstatementlist *aux;
    for (aux = pslb; aux != NULL; aux = aux->next)
    {
        errorcount += check_statement(symtab, aux->u_stat);
    }

    return errorcount;
}

int check_for(table_element **symtab, p_for *pf)
{
    int errorcount = 0;

    if (pf == NULL)
        return errorcount;

    // O type da check_expr tem de ser bool
    const char *type = check_expr(symtab, pf->u_expr);

    if (type == NULL)
    {
        errorcount++;
    }
    if (type && strcmp(type, "bool") != 0)
    {
        errorcount++;
        if (printError)
            printf("Line %d, column %d: Incompatible type %s in for statement\n", pf->id->line, pf->id->column + 1, type);
    }
    errorcount += check_statementlist(symtab, pf->u_statlist);

    return errorcount;
}

// TODO: Check se o return type coincide com o declarado
int check_return(table_element **symtab, p_return *pr)
{
    int errorcount = 0;

    if (pr == NULL)
        return errorcount;

    const char *type = check_expr(symtab, pr->u_expr);

    // Verificar se o type é igual ao return da função
    if (id_function_type && type)
        if (strcmp(id_function_type, type) != 0)
        {
            if (printError)
                printf("Line %d, column %d: Incompatible type %s in return statement\n", pr->id->line, pr->id->column + 1, type);
            errorcount++;
            return errorcount;
        }

    if (id_function_type == NULL)
    {
        if (printError)
            if (type && strcmp(type, "none") && printError)
                printf("Line %d, column %d: Incompatible type %s in return statement\n", pr->id->line, pr->id->column + 1, type);
        errorcount++;
        return errorcount;
    }
    if (type == NULL)
    {
        if (printError)
            printf("Line %d, column %d: Incompatible type undef in return statement\n", pr->id->line, pr->id->column + 1);
        errorcount++;
    }

    return errorcount;
}

int check_funcinvocation(table_element **symtab, is_funcinvocation *ifi)
{
    int errorcount = 0;

    if (ifi == NULL)
        return errorcount;

    errorcount += check_params(symtab, ifi);

    return errorcount;
}

int check_parseargs(table_element **symtab, is_parseargs *ipa)
{
    int errorcount = 0;

    if (ipa == NULL)
        return errorcount;

    const char *type = check_expr(symtab, ipa->u_expr);
    table_element *id = search_id(*symtab, ipa->id->id, true);
    if (id == NULL)
    {
        id = search_id(*global_symtab, ipa->id->id, true);
        if (id == NULL)
        {
            errorcount++;
            if (printError)
                printf("Line %d, column %d: Cannot find symbol %s\n", ipa->id->line, ipa->id->column, id->id->id);
            // TODO: Verificar que quando o id não existe que podemos simplesmente retornar o numero de erros
            return errorcount;
        }
    }

    if (type == NULL)
    {
        errorcount++;
        if (printError)
            printf("Line %d, column %d: Operator strconv.Atoi cannot be applied to types %s, undef\n", ipa->parse->line, ipa->parse->column, id->id->type);
        return errorcount;
    }

    if (strcmp(id->id->type, "int") != 0)
    {
        errorcount++;
        if (printError)
            printf("Line %d, column %d: Operator strconv.Atoi cannot be applied to types %s, %s\n", ipa->parse->line, ipa->parse->column, id->id->type, type);
    }
    else if (strcmp(id->id->type, "int") == 0 && (strcmp(type, "string") != 0 && strcmp(type, "int") != 0))
    {
        errorcount++;
        if (printError)
            printf("Line %d, column %d: Operator strconv.Atoi cannot be applied to types %s, %s\n", ipa->parse->line, ipa->parse->column, id->id->type, type);
    }

    return errorcount;
}

int check_print(table_element **symtab, p_print *p)
{
    int errorcount = 0;

    if (p == NULL)
        return errorcount;

    const char *type = check_expr(symtab, p->u_expr);

    // TODO
    if (printError)
    {
        if (!type && !p->value)
        {
            errorcount++;
            printf("Line %d, column %d: Incompatible type undef in fmt.Println statement\n", p->print->line, p->print->column + 1);
            return errorcount;
        }
    }

    return errorcount;
}

const char *check_expr(table_element **symtab, is_expr *ie)
{
    if (ie != NULL)
    {
        switch (ie->disc_d)
        {
        case d_oper:
            return check_oper(symtab, ie->expr.u_oper);
        case d_signal:
            return check_signal(symtab, ie->expr.u_signal);
        case d_literal:
            return check_literal(symtab, ie->expr.u_literal);
        case d_expr_funcinvocation:
            return check_expr_funcinvocation(symtab, ie->expr.u_funcinvocation);
        case d_expr1:
            return check_expr1(symtab, ie->expr.u_expr1);
        }
    }

    return NULL;
}

const char *check_oper(table_element **symtab, is_oper *io)
{

    if (io != NULL)
    {
        const char *type1 = check_expr(symtab, io->u_expr_left);
        const char *type2 = check_expr(symtab, io->u_expr_right);

        if (!strcmp(io->operator->id, "Plus"))
        {
            return check_error_oper(io, type1, type2, "+");
        }
        if (!strcmp(io->operator->id, "Minus"))
        {
            return check_error_oper(io, type1, type2, "-");
        }
        if (!strcmp(io->operator->id, "Mul"))
        {
            return check_error_oper(io, type1, type2, "*");
        }
        if (!strcmp(io->operator->id, "Div"))
        {
            return check_error_oper(io, type1, type2, "/");
        }
        if (!strcmp(io->operator->id, "Mod"))
        {
            return check_error_oper(io, type1, type2, "%");
        }
        if (!strcmp(io->operator->id, "Eq"))
        {
            return check_error_oper(io, type1, type2, "==");
        }
        if (!strcmp(io->operator->id, "Ge"))
        {
            return check_error_oper(io, type1, type2, ">=");
        }
        if (!strcmp(io->operator->id, "Gt"))
        {
            return check_error_oper(io, type1, type2, ">");
        }
        if (!strcmp(io->operator->id, "Le"))
        {
            return check_error_oper(io, type1, type2, "<=");
        }
        if (!strcmp(io->operator->id, "Lt"))
        {
            return check_error_oper(io, type1, type2, "<");
        }
        if (!strcmp(io->operator->id, "Ne"))
        {
            return check_error_oper(io, type1, type2, "!=");
        }
        if (!strcmp(io->operator->id, "Or"))
        {
            if (type1 && type2 && (!strcmp("bool", type2) || !strcmp("bool", type1)))
                return type1;
            else
            {
                if (type1 == NULL)
                    type1 = (char *)strdup("undef");
                if (type2 == NULL)
                    type2 = (char *)strdup("undef");
                if (printError)
                {
                    exprError = false;
                    printf("Line %d, column %d: Operator || cannot be applied to types %s, %s\n", io->operator->line, io->operator->column, type1, type2);
                }
                return NULL;
            }
        }
        if (!strcmp(io->operator->id, "And"))
        {
            if (type1 && type2 && !strcmp(type1, type2) && !strcmp(type1, "bool"))
                return type1;
            else
            {
                if (type1 == NULL)
                    type1 = (char *)strdup("undef");
                if (type2 == NULL)
                    type2 = (char *)strdup("undef");
                if (printError)
                {
                    exprError = false;
                    printf("Line %d, column %d: Operator && cannot be applied to types %s, %s\n", io->operator->line, io->operator->column, type1, type2);
                }
                return NULL;
            }
        }
    }

    return NULL;
}

const char *check_error_oper(is_oper *io, const char *type1, const char *type2, char *op)
{
    if (type1 && type2)
    {
        if (!strcmp(type1, type2) && !strcmp(op, "+") && strcmp(type1, "bool") != 0)
            return type1;
        else if (!strcmp(type1, type2) && strcmp(type1, "bool") != 0 && (!strcmp(op, "-") || !strcmp(op, "*") || !strcmp(op, "/") || !strcmp(op, "%")) && strcmp(type1, "bool") != 0 && strcmp(type1, "string") != 0)
            return type1;
        else if (!strcmp(type1, type2) && strcmp(type1, "bool") != 0 && (!strcmp(op, "<") || !strcmp(op, "<=") || !strcmp(op, ">") || !strcmp(op, ">=")))
            return "bool";
        else if (!strcmp(type1, type2) && (!strcmp(op, "==") || !strcmp(op, "!=")))
            return "bool";
        else
        {
            if (printError)
            {

                printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", io->operator->line, io->operator->column, op, type1, type2);
                if (!strcmp(op, "<") || !strcmp(op, "<=") || !strcmp(op, ">") || !strcmp(op, ">=") || !strcmp(op, "==") || !strcmp(op, "!="))
                    exprError = false;
            }
            return NULL;
        }
    }
    else
    {
        if (type1 == NULL)
            type1 = (char *)strdup("undef");
        if (type2 == NULL)
            type2 = (char *)strdup("undef");
        if (printError)
        {
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", io->operator->line, io->operator->column, op, type1, type2);
            if (!strcmp(op, "<") || !strcmp(op, "<=") || !strcmp(op, ">") || !strcmp(op, ">=") || !strcmp(op, "==") || !strcmp(op, "!="))
                exprError = false;
        }
        return NULL;
    }
}

const char *check_signal(table_element **symtab, is_signal *is)
{

    if (is != NULL)
    {
        const char *type = check_expr(symtab, is->u_expr);

        // Se tivermos ! com type != bool, dar erro
        if (!strcmp(is->signal->id, "Not"))
        {
            if (!strcmp(type, "bool"))
                return type;
            else
            {
                if (printError)
                {
                    exprError = false;
                    printf("Line %d, column %d: Operator ! cannot be applied to type %s\n", is->signal->line, is->signal->column, type);
                }
                return NULL;
            }
        }

        // Se tivermos - ou + com type != int, dar erro
        if (!strcmp(is->signal->id, "Plus"))
        {
            if (!strcmp(type, "int") || !strcmp(type, "float32"))
                return type;
            else
            {
                if (printError)
                    printf("Line %d, column %d: Operator + cannot be applied to type %s\n", is->signal->line, is->signal->column, type);
                return NULL;
            }
        }
        if (!strcmp(is->signal->id, "Minus"))
        {
            if (!strcmp(type, "int") || !strcmp(type, "float32"))
                return type;
            else
            {
                if (printError)
                    printf("Line %d, column %d: Operator - cannot be applied to type %s\n", is->signal->line, is->signal->column, type);
                return NULL;
            }
        }
    }

    return NULL;
}

const char *check_literal(table_element **symtab, is_literal *il)
{
    if (il != NULL)
    {
        if (!strcmp(il->id, "Id"))
        {
            // Procura na symbol table da função
            table_element *aux = search_id(*symtab, il->value->id, true);
            if (aux == NULL)
            {
                // Procura na symbol table global
                aux = search_id(*global_symtab, il->value->id, true);
                if (aux == NULL)
                {
                    if (printError)
                        printf("Line %d, column %d: Cannot find symbol %s\n", il->value->line, il->value->column, il->value->id);
                }
                else
                    return aux->id->type;
            }
            else
            {
                return aux->id->type;
            }
        }
        if (!strcmp(il->id, "RealLit"))
        {
            return "float32";
        }
        if (!strcmp(il->id, "IntLit"))
        {
            return "int";
        }
    }

    return NULL;
}

const char *check_expr_funcinvocation(table_element **symtab, is_expr_funcinvocation *iefi)
{
    if (iefi != NULL)
    {
        table_element *aux = search_funcdecl(*global_symtab, iefi->u_funcinvocation->id->id);
        if (aux == NULL)
        {
            check_params(symtab, iefi->u_funcinvocation);
            return NULL;
        }
            
        // Verificar se os parâmetros estão de acordo com os declarados
        if (check_params(symtab, iefi->u_funcinvocation) > 0)
            return NULL;
        return aux->funcdec->type;
    }

    return NULL;
}

const char *check_expr1(table_element **symtab, is_expr1 *ie1)
{
    if (ie1 != NULL)
        return check_expr(symtab, ie1->u_expr);

    return NULL;
}

int check_params(table_element **symtab, is_funcinvocation *ifi)
{
    int errorcount = 0;

    // Verificar se a função existe
    table_element *func = search_funcdecl(*global_symtab, ifi->id->id);
    if (func == NULL)
    {
        print_function_error(symtab, ifi);
        errorcount++;
        return errorcount;
    }

    is_exprlist *aux = ifi->u_exprlist;
    t_params *ptype;
    if (aux != NULL && func->funcdec->params != NULL)
    {
        for (ptype = func->funcdec->params; ptype != NULL; aux = aux->next, ptype = ptype->next)
        {
            // Se aux == NULL, temos de dar print ao erro
            if (aux == NULL)
            {
                print_function_error(symtab, ifi);
                errorcount++;
                return errorcount;
            }

            // Se o type dos parametros não for igual, temos de dar print ao erro
            const char *expr = check_expr(symtab, aux->u_expr);
            if (expr)
                if (strcmp(expr, ptype->type) != 0)
                {
                    print_function_error(symtab, ifi);
                    errorcount++;
                    return errorcount;
                }
            if (!expr && ptype->type)
            {
                //TODO: Dar print às expr todas
                if (printError && exprError)
                {
                    //print_function_error(symtab, ifi);
                    print_function_error_undef(symtab, ifi);
                    //printf("Line %d, column %d: Cannot find symbol %s(undef)\n", ifi->id->line, ifi->id->column, ifi->id->id);
                } 
                errorcount++;
                return errorcount;
            }
            exprError = true;
        }
        // Se aux->next != NULL, temos de dar print ao erro
        if (aux != NULL)
        {
            print_function_error(symtab, ifi);
            errorcount++;
            return errorcount;
        }
    }
    else if (aux == NULL && func->funcdec->params != NULL)
    {
        print_function_error(symtab, ifi);
        errorcount++;
        return errorcount;
    }
    else if (aux != NULL && func->funcdec->params == NULL)
    {
        print_function_error(symtab, ifi);
        errorcount++;
        return errorcount;
    }
    return errorcount;
}

void print_function_error(table_element **symtab, is_funcinvocation *ifi)
{
    if (printError)
        printf("Line %d, column %d: Cannot find symbol %s(", ifi->id->line, ifi->id->column, ifi->id->id);

    is_exprlist *aux = ifi->u_exprlist;

    if (aux != NULL && aux->u_expr)
    {
        const char *expr = check_expr(symtab, aux->u_expr);

        if (expr){
            if (printError)
                printf("%s", expr);
        }
        else
            if (printError)
                printf("undef");
        for (aux = aux->next; aux != NULL; aux = aux->next)
        {
            const char *type = check_expr(symtab, aux->u_expr);

            if (printError)
            {
                if (type)
                    printf(",%s", type);
                else
                    printf(",undef");
            }
        }
    }
    if (printError)
        printf(")\n");
}

void print_function_error_undef(table_element **symtab,is_funcinvocation *ifi) 
{
    if (printError)
    {
        printf("Line %d, column %d: Cannot find symbol %s(", ifi->id->line, ifi->id->column, ifi->id->id);

        is_exprlist *aux = ifi->u_exprlist;

        if (aux != NULL && aux->u_expr)
        {
            printError = false;
            const char *expr = check_expr(symtab, aux->u_expr);
            printError = true;

            if (expr)
                printf("%s", expr);
            else
                printf("undef");
            for (aux = aux->next; aux != NULL; aux = aux->next)
            {
                printError = false;
                const char *type = check_expr(symtab, aux->u_expr);
                printError = true;
                if (type)
                    printf(",%s", type);
                else
                    printf(",undef"); 
            }
        }
        printf(")\n");
    }
}
