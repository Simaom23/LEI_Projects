//Ex 10.1.1
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode               // the tree node:
{
    char *word;              // points to the text
    int n_estudante;
    int ano;                   // number of occurrences
    struct tnode *left;      // left child
    struct tnode *right;     // right child
};

struct tnode *addtree(struct tnode *, char *, int, int);

void treeprint(struct tnode *);

int getword(char *, int);

int get_one_line(char *, int);

int main(void) {
    struct tnode *root;
    char word[MAXWORD];
    int num, n_estudante, ano;
    root = NULL;
    while (1) {
        printf("0 - Sair.\n1 - Adicionar Aluno.\n2 - Visualizar lista de alunos.\nEscolha: ");
        scanf("%d", &num);
        if (num == 1) {
            printf("Nome Estudante: ");
            get_one_line(word, MAXWORD);
            printf("Nº Estudante: ");
            scanf("%d", &n_estudante);
            printf("Ano: ");
            scanf("%d", &ano);
            root = addtree(root, word, n_estudante, ano);
        } else if (num == 2) treeprint(root);
        else if (num == 0) break;
    }
    return 0;
}

struct tnode *talloc(void);

char *stringdup(char *);


struct tnode *addtree(struct tnode *p, char *w, int n_estudante, int ano) {
    int cond;
    if (p == NULL)               // a new word has arrived
    {
        p = talloc();            // make a new node
        p->word = stringdup(w);
        p->n_estudante = n_estudante;
        p->ano = ano;
        p->left = p->right = NULL;
        return p;
    }
    cond = strcasecmp(w, p->word);// repeated word
    if (cond < 0)
        p->left = addtree(p->left, w, n_estudante, ano);
    else
        p->right = addtree(p->right, w, n_estudante, ano);
    return p;
}


void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d - %s - %d\n", p->ano, p->word, p->n_estudante);
        treeprint(p->right);
    }
}

#include <stdlib.h>


struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *stringdup(char *s)    // make a duplicate of s
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);   // +1 for '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}

void ungetch(int);

int getch(void);


int get_one_line(char *linha, int lim) {
    int c, i;
    i = 0;
    while (isspace(c = getchar()));
    if (c != EOF) {
        if (!iscntrl(c)) linha[i++] = c;
    } else
        return c;

    for (; i < lim - 1;) {
        c = getchar();
        if (c == EOF)
            return c;
        if (c == '\n')
            break;
        if (!iscntrl(c)) linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = getchar();
    return c;
}
