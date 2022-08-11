#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TAM_LINHA 80
#define MAXNOME 50

int main(void) {
    char *tail, *p;
    char linha[TAM_LINHA], nome[MAXNOME + 1], idade[3];
    int c, invalidos, idade_int, i, j, k, erro;
    FILE *fich = NULL;
    fich = fopen("C:\\ProgramasPPP\\Ex_11.2.11\\nome_idade.txt", "w");
    while (1) {
        i = 0, k = 0, j = 0;
        last = 0;
        erro = 0;
        p = fgets(linha, TAM_LINHA, fich1);
        if (p == NULL) {
            printf("EOF\n");
            break;
        }
        c = strlen(linha);
        if (linha[c - 1] != '\n') {
            printf("Erro - linha demasiado longa\n");
            while ((c = fgetc(stdin)) != EOF && c != '\n');
            continue;
        }
        memset(nome, 0, sizeof(nome));
        while (linha[i] != ';' && i < MAXNOME) {
            if (!isalpha(linha[i]) && linha[i] != ' ') {
                printf("Erro nome inserido incorreto\n");
                erro = 1;
                break;
            }
            if (linha[i] == ' ' && (last == ' ' || last == 0)) {
            } else {
                nome[k] = linha[i];
                k++;
            }
            last = linha[i];
            i++;
        }
        if (last == ' ') {
            nome[k - 1] = 0;
        }
        if (erro == 0) {
            if (i == MAX) {
                printf("Erro - nome demasiado longo\n");
                continue;
            }
            i++;
            while (linha[i] != 'n' && i < MAX) {
                idade[j] = linha[i];
                j++;
                i++;
            }
            //converter
            errno = 0;
            numl = strtol(idade, &tail, 0);
            if (errno) {
                printf("Transbordo em long\n");
                continue;
            }
            // verificar que só há espaço branco no resto da linha
            invalidos = 0;
            while ((*tail) != 0) {
                if (!isspace(*tail)) {
                    printf("Erro - carateres inválidos\n");
                    invalidos = 1;
                    break;
                }
                tail++;
            }
            if (!invalidos && numl < 120) {
                printf("%s -> %d\n", nome, numl);
            } else {
                printf("Erro - valor de idade impossivel\n");
            }
        }
    }
}
