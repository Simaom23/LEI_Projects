// Created by Simão Monteiro on 10/05/2020.
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

#define MAXNOME 100
#define SIZE 50
#define QUOTA 50

static void inicializar_pilha(void);

static struct identidade { // Definir estrutura
    int quotas;
    char nome[MAXNOME + 1];
};

static int push(struct identidade);

void mostrar_tudo(void);

void create_file(FILE *fich_out_a, FILE *fich_out_p);

int insert_pile(FILE *fich_i, FILE *fich_q) {
    static struct identidade pessoa;
    static char quotas_str[SIZE];
    static char nome_str[MAXNOME];
    static int n = 0;
    inicializar_pilha();
    while (fread(nome_str, SIZE, 1, fich_i) && !feof(fich_i)) { // Introdução dos dados contidos no ficheiro binário na pilha
        fread(quotas_str, SIZE, 1, fich_q);                     // São lidos de cada ficheiro binário (Nome+Quota) e introduzidos na pilha como estrutura
        pessoa.quotas = (int) strtol(quotas_str, NULL,0);      // Converte o número que está em forma de string para digíto
        strcpy(pessoa.nome, nome_str);
        n = push(pessoa);   // Coloca na pilha a estrutura pessoa, ou seja, a Identidade (Nome+Quota)
        if (n == 1) printf("Não existe espaço na pilha.");
        fread(quotas_str, SIZE, 1, fich_i); // Ler o /n do ficheiro binário de nomes para nao existir erros de leitura no seguinte loop
        fread(quotas_str, SIZE, 1, fich_q); // Ler o /n do ficheiro quotas de nomes para nao existir erros de leitura no seguinte loop
    }
    return 0;
}

// Estrutura da pilha retirada dos programa exemplos com alterações para o programa em questão
static struct no_pilha {
    struct identidade alguem;
    struct no_pilha *pseg;
} *raiz;

static void inicializar_pilha(void) {
    raiz = NULL;
};

// Colocar na pilha
static int push(struct identidade pessoa) {
    struct no_pilha *aux;
    aux = (struct no_pilha *) malloc(sizeof(struct no_pilha)); // Aloca espaço para inserção na pilha
    if (aux == NULL)
        return 1;
    aux->alguem = pessoa; // Adiciona à pilha a estrutura Identidade (Nome, Quota) através dos ficheiros binários
    aux->pseg = raiz; // O ponteiro para a estrutura seguinte passa a apontar para a antiga raiz
    raiz = aux; // Raiz passa a ser o novo espaço da pilha
    return 0;
}

void pileprint(struct no_pilha *p);

void mostrar_tudo(void) { // Chama a função que percorre e dá print à pilha inteira
    pileprint(raiz);
}

void pileprint(struct no_pilha *p) { // Função que percorre e dá print à pilha inteira
    if (p != NULL) {
        printf("  %s - %d\n", p->alguem.nome, p->alguem.quotas);
        pileprint(p->pseg); // Raiz passa a ser o seguinte em loop até esta ser nula
    }
}

static void lista_npaga(FILE *fich_out_a, struct no_pilha *p);

static void lista_paga(FILE *fich_out_p, struct no_pilha *p);

void create_file(FILE *fich_out_a, FILE *fich_out_p) { // Função que chama as funções para adiconar aos ficheiros de texto
    struct no_pilha *p;
    p = raiz; // Raiz da pilha para comecar a procura
    fprintf(fich_out_a, "As seguintes Identidades têm quotas em atraso [Identidade] [Quotas em atraso]:\n\n"); // Da print no ficheiro com quotas em atraso
    lista_npaga(fich_out_a, p);
    p = raiz;
    fprintf(fich_out_p, "As seguintes Identidades têm as quotas em dia [Identidade] [Quotas pagas a mais]:\n\n"); // Da print no ficheiro com quotas em dia
    lista_paga(fich_out_p, p);
}

static void lista_npaga(FILE *fich_out_a, struct no_pilha *p) { // Esta função cria o ficheiro de texto para as identidades com quotas em atraso
    if (p != NULL) {                                            // A função procura percorre a pilha toda procurando aqueles que tem um pagamento de quotas inferiores a 50
        if (p->alguem.quotas - QUOTA < 0)
            fprintf(fich_out_a, "%s\t%d€\n", p->alguem.nome, QUOTA - p->alguem.quotas);   // E adiciona-os ao ficheiro de texto
        lista_npaga(fich_out_a, p->pseg); // Raiz passa a ser o elemento seguinte e chamasse sucessivamente a função até a raiz ser nula
    }
}

static void lista_paga(FILE *fich_out_p, struct no_pilha *p) {  // Esta função cria o ficheiro de texto para as identidades com quotas em dia
    if (p != NULL) {                                            // A função procura percorre a pilha toda procurando aqueles que tem um pagamento de quotas superiores ou iguais a 50
        if (p->alguem.quotas - QUOTA >= 0)
            fprintf(fich_out_p, "%s\t%d€\n", p->alguem.nome, p->alguem.quotas - QUOTA); // E adiciona-os ao ficheiro de texto
        lista_paga(fich_out_p, p->pseg); // Raiz passa a ser o elemento seguinte e chamasse sucessivamente a função até a raiz ser nula
    }
}
