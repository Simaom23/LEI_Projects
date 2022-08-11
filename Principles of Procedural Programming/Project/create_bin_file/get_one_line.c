#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "get_one_line.h"
// Função criada pelo professor com uma simples alteração
// Sendo esta alteração que aceita a introdução de Nomes e Quotas(Numeros) na mesma linha com a separação por uma vírgula
int get_one_line(FILE *fich, char *linha, int lim) {
    int c, i;
    i = 0;
    while (isspace(c = fgetc(fich)));
    if (c != EOF) {
        if (!iscntrl(c)) linha[i++] = c;
    } else
        return c;
    for (; i < lim - 1;) {
        c = fgetc(fich);
        if (c == EOF || c == ','){ // Linha onde alterei a função.
            linha[i++]='\0';
            return c;
        }
        if (c == '\n')
            break;
        if (!iscntrl(c)) linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);
    return c;
}
