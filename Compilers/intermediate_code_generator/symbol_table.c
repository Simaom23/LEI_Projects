/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

// Libraries
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Global Variables
extern table_element *symtab;

/*************************** Insert Functions ***************************/

// Insere um novo identificador na cauda de uma lista ligada de simbolo
table_element *insert_id(table_element **symtab, char *str, int line, int column, char *t, bool param)
{
  table_element *newSymbol = (table_element *)malloc(sizeof(table_element));
  t_id *tid = (t_id *)malloc(sizeof(t_id));
  table_element *aux;
  table_element *previous;

  tid->id = (char *)strdup(str);
  t[0] = tolower(t[0]);
  tid->line = line;
  tid->column = column;
  tid->type = t;
  tid->used = false;
  tid->seen = false;
  tid->param = param;
  tid->reg = 0;

  newSymbol->id = tid;
  newSymbol->funcdec = NULL;
  newSymbol->next = NULL;

  if (*symtab)
  {
    for (aux = *symtab; aux; previous = aux, aux = aux->next)
    {
      if (aux->id)
        if (strcmp(aux->id->id, str) == 0)
        {
          free(newSymbol->id->id);
          free(newSymbol);
          return NULL;
        }
    }
    previous->next = newSymbol;
  }
  else
  {
    *symtab = newSymbol;
  }

  return newSymbol;
}

// Insere uma nova function declaration na cauda de uma lista ligada de simbolo
table_element *insert_func(table_element **symtab, char *str, char *t)
{
  table_element *newSymbol = (table_element *)malloc(sizeof(table_element));
  t_funcdec *tf = (t_funcdec *)malloc(sizeof(t_funcdec));
  table_element *aux;
  table_element *previous;

  tf->id = (char *)strdup(str);
  tf->params = NULL;
  if (t)
    t[0] = tolower(t[0]);
  if (t)
    tf->type = t;
  else
    tf->type = (char *)strdup("none");
  tf->seen = false;

  newSymbol->funcdec = tf;
  newSymbol->id = NULL;
  newSymbol->next = NULL;

  if (*symtab)
  {
    for (aux = *symtab; aux; previous = aux, aux = aux->next)
    {
      if (aux->funcdec)
        if (strcmp(aux->funcdec->id, str) == 0)
        {
          free(newSymbol->funcdec->id);
          free(newSymbol);
          return NULL;
        }
    }
    previous->next = newSymbol;
  }
  else
  {
    *symtab = newSymbol;
  }

  return newSymbol;
}

// Insere um parâmetro
void insert_params(t_funcdec *fd, char *id, char *type)
{
  t_params *t = (t_params *)malloc(sizeof(t_params));
  t_params *tmp;

  t->id = (char *)strdup(id);
  t->next = NULL;

  type[0] = tolower(type[0]);
  t->type = type;
  t->seen = false;

  if (fd->params == NULL)
  {
    fd->params = t;
    return;
  }

  for (tmp = fd->params; tmp->next != NULL; tmp = tmp->next)
    ;
  tmp->next = t;

  return;
}

/*************************** Print Functions ***************************/

void show_table(table_element *symtab)
{
  table_element *aux;

  for (aux = symtab; aux; aux = aux->next)
  {
    if (aux->id)
    {
      if (aux->id->param)
        printf("%s\t\t%s\tparam\n", aux->id->id, aux->id->type);
      else
        printf("%s\t\t%s\n", aux->id->id, aux->id->type);
    }
    else
    {
      printf("%s\t(", aux->funcdec->id);
      print_params(aux->funcdec->params);

      if (aux->funcdec->type)
      {
        printf(")\t%s\n", aux->funcdec->type);
      }
      else
      {
        printf(")\tnone\n");
        aux->funcdec->type = (char *)strdup("none");
      }
    }
  }
  printf("\n");
}

void print_params(t_params *params)
{
  t_params *p;
  if (params == NULL)
    return;

  printf("%s", params->type);
  for (p = params->next; p != NULL; p = p->next)
  {
    printf(",%s", p->type);
  }
}
/*************************** Search Functions ***************************/

// Procura um identificador, devolve NULL caso nao exista
table_element *search_id(table_element *symtab, char *str, bool used)
{
  table_element *aux;
  for (aux = symtab; aux; aux = aux->next)
    if (aux->id)
      if (!strcmp(aux->id->id, str))
      {
        if (used)
          aux->id->used = true;
        return aux;
      }

  return NULL;
}

// Procura uma declaração de função, devolve NULL caso nao exista
table_element *search_funcdecl(table_element *symtab, char *str)
{
  table_element *aux;

  for (aux = symtab; aux; aux = aux->next)
    if (aux->funcdec)
      if (!strcmp(aux->funcdec->id, str))
        return aux;

  return NULL;
}
