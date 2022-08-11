/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "tree.h"
#include "symbol_table.h"
#include "llvm.h"

// Global Variables
table_element **global_symtab;
int varCount = 1, useVar = 0;
char *funcType;

char *llvm_type(char *type)
{
    if (!strcmp(type, "int"))
        return "i32";
    else if (!strcmp(type, "float32"))
        return "double";
    else if (!strcmp(type, "bool"))
        return "i1";
    else if (!strcmp(type, "string"))
        return "i8*";
    return "void";
}

void fmt_println()
{
    printf("\ndefine void @fmt.Prinln(i1 %%bool) {\n");
    printf("\tbr i1 %%bool, label %%true, label %%false\n");
    printf("\ttrue:\n");
    printf("\tcall i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.print_true, i8 0, i8 0))\n");
    printf("\tret void\n");
    printf("\tfalse:\n");
    printf("\tcall i32 (i8*, ...) @printf(i8* getelementptr ([7 x i8], [7 x i8]* @.print_false, i8 0, i8 0))\n");
    printf("\tret void\n}\n");
}

void program(is_program *p)
{
    global_symtab = &p->symtab;
    if (p)
    {
        printf("declare i32 @printf(i8*, ...)\n");
        printf("declare i32 @atoi(...)\n\n");
        printf("@.empty_str = constant [1 x i8] c\"\\00\"\n");
        printf("@.print_int = constant [4 x i8] c\"%%d\\0A\\00\"\n");
        printf("@.print_float = constant [7 x i8] c\"%%.08f\\0A\\00\"\n");
        printf("@.print_str = constant [4 x i8] c\"%%s\\0A\\00\"\n");
        printf("@.print_false = constant [7 x i8] c\"false\\0A\\00\"\n");
        printf("@.print_true = constant [6 x i8] c\"true\\0A\\00\"\n");
        fmt_println();
        declarations(&p->symtab, p->u_decl);
    }
}

void declarations(table_element **symtab, is_declarations *id)
{
    if (id)
    {
        for (; id != NULL; id = id->next)
        {
            vardecl(symtab, id->u_vardecl);
            funcdecl(symtab, id->u_funcdecl);
        }
    }
    return;
}

void funcdecl(table_element **symtab, is_funcdecl *ifd)
{
    if (ifd)
    {
        table_element *table = search_funcdecl(*global_symtab, ifd->id->id);
        if (table->funcdec)
        {
            varCount = 1;
            if (!strcmp(table->funcdec->id, "main"))
            {
                funcType = llvm_type(table->funcdec->type);
                printf("\ndefine %s @%s(i32 %%argc, i8** %%argv) {\n", funcType, table->funcdec->id);
                function_body(&ifd->symtab, ifd->u_funcbody);
            }
            else
            {
                funcType = llvm_type(table->funcdec->type);
                printf("\ndefine %s @%s(", funcType, table->funcdec->id);
                function_header(&table, ifd->u_parameters);
                paramdecl(&table, &ifd->symtab, ifd->u_parameters);
                function_body(&ifd->symtab, ifd->u_funcbody);
            }
            printf("}\n");
        }
    }
    return;
}
void paramdecl(table_element **symtab_func, table_element **symtab_vars, is_parameters *ip)
{
    if (ip)
    {
        table_element *table = *symtab_func;
        if (table->funcdec)
        {
            for (t_params *params = table->funcdec->params; params != NULL; params = params->next)
            {
                table_element *var = search_id(*symtab_vars, params->id, false);
                printf("\t%%%d = alloca %s\n", varCount, llvm_type(params->type));
                printf("\tstore %s %%%s, %s* %%%d\n", llvm_type(params->type), params->id, llvm_type(params->type), varCount);
                var->id->reg = varCount;
                varCount++;
            }
        }
    }
    return;
}

void vardecl(table_element **symtab, is_vardecl *ivd)
{
    if (ivd)
    {
        table_element *table = *symtab;
        for (; table != NULL; table = table->next)
        {
            if (table->id)
            {
                if (!table->id->param)
                {
                    if (symtab == global_symtab)
                        if (!strcmp(llvm_type(table->id->type), "i8*"))
                            printf("@%s = global %s null\n", table->id->id, llvm_type(table->id->type));
                        else
                            printf("@%s = global %s 0\n", table->id->id, llvm_type(table->id->type));

                    else
                    {
                        table->id->reg = varCount;
                        printf("\t%%%d = alloca %s\n", varCount, llvm_type(table->id->type));
                        varCount++;
                    }
                }
            }
        }
    }
    return;
}

void function_header(table_element **symtab, is_parameters *ip)
{
    if (ip)
    {
        table_element *table = *symtab;
        if (table->funcdec)
        {
            for (t_params *params = table->funcdec->params; params != NULL; params = params->next)
            {
                if (params->next)
                    printf("%s %%%s, ", llvm_type(params->type), params->id);
                else
                    printf("%s %%%s", llvm_type(params->type), params->id);
            }
        }
    }
    printf(") {\n");
    return;
}

void function_body(table_element **symtab, is_funcbody *ifb)
{
    if (ifb)
    {
        is_varsandstatements *body = ifb->u_varsandstatements;
        for (; body != NULL; body = body->next)
        {
            if (body->u_stat)
                statement(symtab, body->u_stat);
            if (body->u_vardec)
                vardecl(symtab, body->u_vardec);
        }
    }
    return;
}

void statement(table_element **symtab, is_statement *is)
{
    if (is)
    {
        switch (is->disc_d)
        {
        case d_idexpr:
            llvm_idexpr(symtab, is->prod.u_idexpr);
            break;

        case d_return:
            llvm_return(symtab, is->prod.u_return);
            break;

        case d_funcinvocation:
            funcinvocation(symtab, is->prod.u_funcinvocation);
            break;

        case d_parseargs:
            parseargs(symtab, is->prod.u_parseargs);
            break;

        case d_print:
            llvm_print(symtab, is->prod.u_print);
            break;

        case d_statlist:
            statementlist(symtab, is->prod.u_statlist);
            break;

        case d_bstatlist:
            bstatementlist(symtab, is->prod.u_bstatlist);
            break;

        case d_if:
            llvm_if(symtab, is->prod.u_if);
            break;

        case d_for:
            llvm_for(symtab, is->prod.u_for);
            break;

        default:
            break;
        }
    }
    return;
}

void llvm_idexpr(table_element **symtab, p_id_expr *pie)
{
    if (pie)
    {
        table_element *var = search_id(*symtab, pie->id->id, false);
        if (!var)
            var = search_id(*global_symtab, pie->id->id, false);
        if (var->id->reg != 0)
        {
            useVar = var->id->reg;
        }
        expr(symtab, pie->u_expr);
        // printf("\t%%%d = load %s, %s* %%%d\n", varCount, llvm_type(var->id->type), llvm_type(var->id->type), varCount - 1);
        useVar = 0;
    }
    return;
}

void llvm_return(table_element **symtab, p_return *pr)
{
    if (pr)
    {
        expr(symtab, pr->u_expr);
        printf("\tret %s %%%d\n", funcType, varCount - 1);
    }
    return;
}

void funcinvocation(table_element **symtab, is_funcinvocation *ifi)
{
    if (ifi)
    {
        expr_list(symtab, ifi->u_exprlist);
        table_element *func = search_funcdecl(*global_symtab, ifi->id->id);
        printf("\t%%%d = call %s @%s(\n", varCount, llvm_type(func->funcdec->type), func->funcdec->id);
        varCount++;
    }
    return;
}

void parseargs(table_element **symtab, is_parseargs *ipa)
{
    if (ipa)
    {
        return;
    }
    return;
}

void llvm_print(table_element **symtab, p_print *pp)
{
    expr(symtab, pp->u_expr);
    // printf("%%%d = call i32 (i8*, ...) @printf(i8* %%%s)");
    return;
}

void statementlist(table_element **symtab, p_statementlist *psl)
{
    for (; psl != NULL; psl = psl->next)
        statement(symtab, psl->u_stat);
    return;
}

void bstatementlist(table_element **symtab, p_bstatementlist *pbsl)
{
    for (; pbsl != NULL; pbsl = pbsl->next)
        statement(symtab, pbsl->u_stat);
    return;
}

void llvm_if(table_element **symtab, p_if *pi)
{
    if (pi)
    {
        expr(symtab, pi->u_expr);
        printf("\tbr i1 %%%d, label %%%d, label %%%d\n", varCount, varCount + 1, varCount + 2);
        varCount++;
        printf("\n;\t<label>:%d:\n", varCount);
        statementlist(symtab, pi->u_statlist);
        printf("\n;\t<label>:%d:\n", varCount);
        if (pi->u_statlistop)
            statementlist(symtab, pi->u_statlistop);
    }
    return;
}

void llvm_for(table_element **symtab, p_for *pf)
{
    return;
}

void expr_list(table_element **symtab, is_exprlist *iel)
{
    if (iel)
    {
        for (; iel != NULL; iel = iel->next)
            expr(symtab, iel->u_expr);
    }
    return;
}

char *expr(table_element **symtab, is_expr *ie)
{
    if (ie)
    {
        switch (ie->disc_d)
        {
        case d_oper:
            oper(symtab, ie->expr.u_oper);
            break;

        case d_signal:
            signal(symtab, ie->expr.u_signal);
            break;

        case d_literal:
            literal(symtab, ie->expr.u_literal);
            break;

        case d_expr_funcinvocation:
            expr_funcinvocation(symtab, ie->expr.u_funcinvocation);
            break;

        case d_expr1:
            expr1(symtab, ie->expr.u_expr1);
            break;

        default:
            break;
        }
    }
    return NULL;
}

char *oper(table_element **symtab, is_oper *io)
{
    if (io)
    {
        char *type1 = expr(symtab, io->u_expr_left);
        expr(symtab, io->u_expr_right);
        if (!strcmp(io->operator->id, "Plus"))
        {
            printf("\t%%%d = add nsw %%%s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            varCount++;
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Minus"))
        {
            printf("\t%%%d = sub nsw %%%s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            varCount++;
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Mul"))
        {
            printf("\t%%%d = mul nsw %%%s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            varCount++;
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Div"))
        {
            printf("\t%%%d = sdiv %%%s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            varCount++;
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Mod"))
        {
            printf("\t%%%d = srem %%%s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            varCount++;
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Eq"))
        {
            printf("\t%%%d = icmp eq %s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Ge"))
        {
            printf("\t%%%d = icmp sge %s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Gt"))
        {
            printf("\t%%%d = icmp sgt %s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Le"))
        {
            printf("\t%%%d = icmp sle %s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Lt"))
        {
            printf("\t%%%d = icmp slt %s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Ne"))
        {
            printf("\t%%%d = icmp ne %s %%%d, %%%d\n", varCount, type1, varCount - 1, varCount - 2);
            return NULL;
        }
        else if (!strcmp(io->operator->id, "Or"))
        {
            return NULL;
        }
        else if (!strcmp(io->operator->id, "And"))
        {
            return NULL;
        }
    }
    return NULL;
}

char *signal(table_element **symtab, is_signal *is)
{
    return NULL;
}

char *literal(table_element **symtab, is_literal *il)
{
    if (il)
    {
        if (!strcmp(il->id, "Id"))
        {
            table_element *var = search_id(*symtab, il->value->id, false);
            if (var == NULL)
                var = search_id(*global_symtab, il->value->id, false);

            printf("\t%%%d = load %s, %s* %%%d\n", varCount, llvm_type(var->id->type), llvm_type(var->id->type), var->id->reg);
            varCount++;
            return llvm_type(var->id->type);
        }
        else if (!strcmp(il->id, "RealLit"))
        {
            if (useVar == 0)
            {
                printf("\t%%%d = alloca double\n", varCount);
                printf("\tstore double %s, double* %%%d\n", il->value->id, varCount);
                varCount++;
            }
            else
            {
                printf("\tstore double %s, double* %%%d\n", il->value->id, useVar);
            }
            return "double";
        }
        else if (!strcmp(il->id, "IntLit"))
        {
            if (useVar == 0)
            {
                printf("\t%%%d = alloca i32\n", varCount);
                printf("\tstore i32 %s, i32* %%%d\n", il->value->id, varCount);
                varCount++;
            }
            else
            {
                printf("\tstore i32 %s, i32* %%%d\n", il->value->id, useVar);
            }
            return "i32";
        }
    }
    return NULL;
}

char *expr_funcinvocation(table_element **symtab, is_expr_funcinvocation *iefi)
{
    funcinvocation(symtab, iefi->u_funcinvocation);
    return NULL;
}

char *expr1(table_element **symtab, is_expr1 *ie1)
{
    return expr(symtab, ie1->u_expr);
}
