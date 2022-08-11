#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXNOME 100
#define MAXLINHA 40

int main() {
    char nome_fich[MAXNOME];
    char linha[MAXLINHA + 1];
    char palavra[MAXNOME];
    char c;
    int cont = 0, i = 0;
    FILE *fich = NULL;
    printf("Nome do ficheiro? ");
    scanf("%s", nome_fich);
    fich = fopen(nome_fich, "r");
    while (c = fgetc(fich) && !feof(fich)) {
        if (c != ' ') palavra[i] = c;
        if (cont == 40 && isalpha(c=fich)) {
            printf("%s", linha);
            strcpy(linha,"");
        }
        if (c == ' ') {
            palavra[++i] = ' ';
            strcat(linha, palavra);
            strcpy(palavra, "");
            i = -1;
        }
        i++;
        cont++;
    }
    fclose(fich);
    return 0;
}
