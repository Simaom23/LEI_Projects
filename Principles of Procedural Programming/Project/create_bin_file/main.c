#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "get_one_line.h"

#define MAXNOME 100
#define SIZE 50

int main() {
    char quotas_str[SIZE];
    char nome[MAXNOME];
    char n_str[10];
    int n;
    FILE *fich_q = NULL;
    FILE *fich_i = NULL;
    // Loop infinito até o utilizador decidir sair
    while (1) {
        printf("\n0 - Sair\n1 - Criar Ficheiro Binário\n2 - Retirar do Ficheiro\n3 - Acrescentar ao Ficheiro\nEscolha: ");
        scanf("%d", &n);
        // A função em baixo cria dois ficheiros binários snedo que o utilizador introduz várias Identidades de uma vez (Nome,Quota)
        // Estes são separados nos dois ficheiros binários um com os nomes e outro com as quotas de cada identidade por ordem de entrada
        if (n == 1) {
            fich_i = fopen("Identidades.bin", "w");
            fich_q = fopen("Quotas.bin", "w");
            printf("Introduza as Identidades (Nome,Quotas):\n");
            // Enquanto o utilizador introduzir identidades ou não escreve fim a função adiciona o nome e a quota aos respetivos ficheiros binários
            // Lê-se do stdin e introduz-se em cada ficheiro binário respetivo
            while (get_one_line(stdin, nome, MAXNOME + 1) != EOF && strcasecmp(nome, "Fim") != 0) {
                if (get_one_line(stdin, quotas_str, 6) != EOF) {
                    fwrite(nome, SIZE, 1, fich_i);
                    fwrite(quotas_str, SIZE, 1, fich_q);
                    fwrite("\n", SIZE, 1, fich_q);
                    fwrite("\n", SIZE, 1, fich_i);
                }
            }
            fclose(fich_q);
            fclose(fich_i);
            printf("Foram criados dois ficheiros com os nomes Quotas.bin e Identidades.bin.\n");
            // A função em baixo adiciona elimina dos dois ficheiros binários uma identidade ou seja retira o nome de um ficheiro e a quota do outro
        } else if (n == 2) {
            char delete_name[MAXNOME];
            int flag = 0;
            FILE *temp_file = NULL;
            temp_file = fopen("temp_file.bin", "w"); //Criar um ficheiro temporario
            fich_q = fopen("Quotas.bin", "r");
            fich_i = fopen("Identidades.bin", "r");
            fgetc(stdin);
            printf("Qual Identidade deseja eliminar? ");
            fgets(delete_name, MAXNOME, stdin);
            if (delete_name[strlen(delete_name)] == '\0' && delete_name[strlen(delete_name) - 1] != '\n') { // Se o utilizador introduzir um nome não permitido
                printf("Nome inserido nao permitido. Tente Novamente.\n");                                  // o programa é interrompido e é dada uma mensagem de erro
                break;
            }
            delete_name[strlen(delete_name) - 1] = '\0'; // Retira o "\n" acrescentado pelo fgets
            while (fread(nome, SIZE, 1, fich_i) && !feof(fich_i)) { // É lido do ficheiro Identidades.bin e Quotas.bin e escrito no ficheiro temporário
                fread(quotas_str, SIZE, 1, fich_q);                 // Caso seja encontrada a Identidade a eliminar o programa passa à frente e nao escreve no ficheiro temp
                if (strcasecmp(delete_name, nome) != 0) {
                    fwrite(nome, SIZE, 1, temp_file);
                    fwrite(quotas_str, SIZE, 1, temp_file);
                    fwrite("\n", SIZE, 1, temp_file);
                } else flag = 1;
                fread(quotas_str, SIZE, 1, fich_i);
                fread(quotas_str, SIZE, 1, fich_q);
            }
            fclose(fich_q);
            fclose(fich_i);
            fclose(temp_file);
            fich_q = fopen("Quotas.bin", "w");
            fich_i = fopen("Identidades.bin", "w");
            temp_file = fopen("temp_file.bin", "r");
            while (fread(nome, SIZE, 1, temp_file) && !feof(temp_file)) { // Assim os ficheiros Identidades.bin e Quotas.bin são reescritos
                fread(quotas_str, SIZE, 1, temp_file);                    // Ou seja sao lidos os nome e as quotas do ficheiro e dividos nos respetivos ficheiro binários
                fwrite(nome, SIZE, 1, fich_i);
                fwrite("\n", SIZE, 1, fich_i);
                fwrite(quotas_str, SIZE, 1, fich_q);
                fwrite("\n", SIZE, 1, fich_q);
                fread(quotas_str, SIZE, 1, temp_file);
            }
            fclose(fich_q);
            fclose(fich_i);
            fclose(temp_file);
            remove("temp_file.bin");
            if (flag == 1) printf("O nome foi retirado com sucesso.");
            else printf("O nome nao foi retirado pois nao existia no ficheiro ou existiu um erro.");
        }
            // A função em baixo adiciona aos dois ficheiros binários endo que o utilizador introduz as várias Identidades que deseja acrescentar (Nome,Quota)
            // Estes são separados nos dois ficheiros binários um com os nomes e outro com as quotas de cada identidade por ordem de entrada depois dos dados já introduzidos anteriormente
        else if (n == 3) {
            fich_i = fopen("Identidades.bin", "a");
            fich_q = fopen("Quotas.bin", "a");
            printf("Introduza as Identidades (Nome,Quotas) que deseja acrescentar:\n");
            // Equivalente à função de criar ficheiro mas apenas adiciona ao que contem no ficheiro usando o mesmo tipo de esquema
            // Lê-se do stdin e acresecentasse os nomes e as quotas a cada ficheiro correspondente
            while (get_one_line(stdin, nome, MAXNOME + 1) != EOF && strcasecmp(nome, "Fim") != 0) {
                if (get_one_line(stdin, quotas_str, 6) != EOF) {
                    fwrite(nome, SIZE, 1, fich_i);
                    fwrite(quotas_str, SIZE, 1, fich_q);
                    fwrite("\n", SIZE, 1, fich_q);
                    fwrite("\n", SIZE, 1, fich_i);
                }
            }
            fclose(fich_q);
            fclose(fich_i);
        } else if (n == 0) // Sai do loop
            break;
        else if (n > 3 || n < 0) printf("Introduza uma opção válida.");
    }
    return 0;
}

