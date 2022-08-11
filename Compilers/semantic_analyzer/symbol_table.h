/* Maria Dias 2018274188    Simão Monteiro 2019215412 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>

typedef struct _t4
{
  bool seen;
  char *id;
  char *type;
  struct _t4 *next;
} t_params;

typedef struct _t3
{
  bool seen;
  char *id;
  char *type;
  t_params *params;
} t_funcdec;

typedef struct _t2
{
  int line;
  int column;
  bool seen;
  bool used;
  char *id;
  char *type;
  bool param;
} t_id;

typedef struct _t1
{
  t_id *id;
  t_funcdec *funcdec;
  struct _t1 *next;
} table_element;

table_element *insert_id(table_element **symtab, char *str, int line, int column, char *t, bool param);
table_element *insert_func(table_element **symtab, char *str, char *t);
void insert_params(t_funcdec *fd, char *id, char *type);

table_element *search_id(table_element *symtab, char *str, bool used);
table_element *search_funcdecl(table_element *symtab, char *str);

void show_table(table_element *symtab);
void print_params(t_params *params);

#endif
