#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXNOME 100
#define MAXLINHA 40

struct peca {
    char ref[MAXNOME + 1];
    char des[MAXNOME + 1];
    int n_pecas;
};

void inicializar_arvore(void);

int colocar(struct peca pc);

void mostrar_tudo(void);

int get_one_line(FILE *fich, char *linha, int lim);

void criar_fich(FILE *);

int main() {
    struct peca pc;
    char quantity[MAXNOME];
    FILE *fich = NULL;
    FILE *fich_out = NULL;
    fich = fopen("C:\\ProgramasPPP\\11.2.12\\pecas.txt", "r");
    while (get_one_line(fich, pc.ref, MAXNOME) && !feof(fich)) {
        get_one_line(fich, pc.des, MAXNOME);
        get_one_line(fich, quantity, MAXNOME);
        pc.n_pecas = (int) strtol(quantity, NULL, 0);
        colocar(pc);
    }
    mostrar_tudo();
    fclose(fich);
    fich_out = fopen("C:\\ProgramasPPP\\11.2.12\\pecas_reduzidas.txt", "w");
    fprintf(fich_out, "As peças com uma quantidade menor a 10 estão abaixo listadas:\n");
    criar_fich(fich_out);
    fclose(fich_out);
    return 0;
}

struct tnode {
    struct peca pecas;
    struct tnode *left;
    struct tnode *right;
} *raiz;

void inicializar_arvore(void) {
    raiz = NULL;
}

struct tnode *addtree(struct tnode *, struct tnode *);

int colocar(struct peca pc) {
    struct tnode *p;
    p = (struct tnode *) malloc(sizeof(struct tnode));
    if (p == NULL)
        return 1;
    p->pecas = pc;
    p->left = p->right = NULL;
    raiz = addtree(raiz, p);
    return 0;
}

struct tnode *addtree(struct tnode *pr, struct tnode *p) {
    int cond;
    if (pr == NULL) {
        pr = p;
    } else {
        if ((cond = strcasecmp(p->pecas.ref, pr->pecas.ref)) > 0) {
            pr->right = addtree(pr->right, p);
        } else if (cond < 0)
            pr->left = addtree(pr->left, p);
    }
    return pr;
}

void treeprint(struct tnode *p);

void mostrar_tudo(void) {
    treeprint(raiz);
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s - %s - %d\n", p->pecas.ref, p->pecas.des, p->pecas.n_pecas);
        treeprint(p->right);
    }
}

void printing(struct tnode *p, FILE *);

void criar_fich(FILE *fich_out) {
    printing(raiz, fich_out);
}

void printing(struct tnode *p, FILE *fich_out) {
    if (p != NULL) {
        printing(p->left, fich_out);
        if (p->pecas.n_pecas < 10)
            fprintf(fich_out, "%s - %s\n", p->pecas.ref, p->pecas.des);
        printing(p->right, fich_out);
    }
}

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
        if (c == EOF || c == ',') {
            linha[i++] = '\0';
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