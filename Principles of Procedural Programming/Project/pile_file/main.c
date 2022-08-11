// Created by Simão Monteiro on 10/05/2020.
/* Visto que no enuciado não diz quais opções usar para alteração do ficheiro,
 * eu decidi criar tres funções. Uma função de criar os ficheiros binários, uma
 * de eliminar identidades dos ficheiros binários e outra de adicionar mais identidades
 * aos ficheiros binários .
 * Também no programa principal duas várias opcões. Uma para Mostar os conteúdos da pilha
 * e outra para criar os ficheiros de texto pedindo o nome de ambos os ficheiros de saída
 * (As listagens quotas em dia e quotas em atraso)
 * As quotas pagas sao todas inteiras sem viirgula flutuante
 * Problemas previstos e não resolvidos: O scanf do programa de criação de ficheiros
 *  caso não seja inserido um número ou seja um número muito grande poderá crashar o programa de criação.*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

#define MAXNOME 100

int main(int argc, char *argv[]) {
    int n;
    FILE *file_i = NULL;
    FILE *file_q = NULL;
    FILE *file_out_a = NULL;
    FILE *file_out_p = NULL;
    char nome_fich_a[MAXNOME];
    char nome_fich_p[MAXNOME];
    /*char *prog = argv[0];
    if (argc == 3) {
        if ((file_i = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, argv[1]);
            exit(1);
        }
        if ((file_q = fopen(argv[2], "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, argv[1]);
            exit(1);
        }
    } else {
        fprintf(stderr, "%s: Erro! Introduza os nomes corretos dos dois ficheiros de entrada (Identidades e Quotas).\n", prog);
        exit(1);
    }*/
    file_i = fopen("Identidades.bin", "r");
    file_q = fopen("Quotas.bin", "r");
    insert_pile(file_i, file_q); // Nesta função é adicionado à pilha as identidades e respetivas quotas
    fclose(file_i);
    fclose(file_q);
    while (1) {
        printf("\n0 - Sair\n1 - Mostrar conteúdo da pilha\n2 - Criar os ficheiros de texto\nEscolha: ");
        scanf("%d", &n);
        if (n == 1) {
            printf("\nNa pilha estão inseridas as Identidades (Nome/Quota):\n");
            mostrar_tudo(); // Mostra o conteúdo da pilha todo
        } else if (n == 2) {
            fgetc(stdin);
            printf("\nIntroduza o nome de ficheiro de saída para as Identidades com quotas em atraso:\n");
            fgets(nome_fich_a, MAXNOME, stdin);
            if (nome_fich_a[strlen(nome_fich_a)] == '\0' && nome_fich_a[strlen(nome_fich_a) - 1] != '\n') { // Se o utlizador introduzir um nome de ficheiro nao permitido
                printf("\nErro. Nome de ficheiro nao permitido.\nTente Novamente.\n");                      // é dada uma mensagem de erro e programa para
                break;
            }
            nome_fich_a[strlen(nome_fich_a) - 1] = '\0'; // Retira o "\n" que fgets acrescenta também
            printf("\nIntroduza o nome de ficheiro de saída para as Identidades com quotas em dia:\n");
            fgets(nome_fich_p, MAXNOME, stdin);
            if (nome_fich_p[strlen(nome_fich_p)] == '\0' && nome_fich_p[strlen(nome_fich_p) - 1] != '\n') {
                printf("Erro. Nome de ficheiro nao permitido.\nTente Novamente.\n");
                break;
            }
            nome_fich_p[strlen(nome_fich_p) - 1] = '\0';
            file_out_a = fopen(nome_fich_a, "w");
            file_out_p = fopen(nome_fich_p, "w");
            create_file(file_out_a,file_out_p); // Esta função está criada no ficheiro fonte da pilha que chama duas funçoes para criar os dois ficheiros de texto
            fclose(file_out_a);
            fclose(file_out_p);
            if ((file_out_a = fopen(nome_fich_a, "r")) == NULL || (file_out_p = fopen(nome_fich_p, "r")) == NULL) printf("\nExistiu um erro na criação dos ficheiros. Tente novamente.\n");
            else printf("\nOs ficheiros foram criados com sucesso.\n");
            fclose(file_out_a);
            fclose(file_out_p);
        } else if (n == 0) break;
        else if (n > 2 || n < 0) printf("Introduza uma opção válida.");
    }
    return 0;
}
