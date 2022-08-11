#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//11.1.1
/*#define MAXNOME 100

void clean_cr(FILE *);

int get_one_line(FILE *fich, char *linha, int lim);

int main(void) {
    char nome_fich[MAXNOME + 1];
    FILE *fich = NULL;
    while (fich == NULL) {
        printf("Nome do ficheiro de dados? ");
        if (get_one_line(stdin, nome_fich, MAXNOME + 1) == EOF)
            return 0;
        fich = fopen(nome_fich, "a");
        if (fich == NULL)
            fprintf(stderr, "Ficheiro não existe\n");
    }
    clean_cr(fich);
    return 0;
}
void clean_cr(FILE *fich){
    char c1,c2;
    while(c1=(fgetc(fich))!=NULL){
        if(c1=0x0d)
            c2=c1;
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
        if (c == EOF)
            return c;
        if (c == '\n')
            break;
        if (!iscntrl(c)) linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);
    return c;
}
//11.2.1
#define MAXNOME 100

int get_one_line(char *linha, int lim);

char *size(FILE *, char *);

int acrescentar(FILE *, char *);

void palindromo(FILE *);

int main(void) {
    FILE *fich = NULL;
    char nome[MAXNOME + 1];
    int tamanho = 0;
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "w");
    printf("Insira as plavras que deseja introduzir no ficheiro: ");
    while (get_one_line(nome, MAXNOME + 1) != EOF && strcasecmp(nome, "Fim") != 0)
        fprintf(fich, "%s\n", nome);
    fclose(fich);
    printf("A palavra com o maior número de carateres é: %s", size(fich, nome));
    acrescentar(fich, nome);
    palindromo(fich);
    return 0;
}

char *size(FILE *fich, char *nome) {
    char s[MAXNOME + 1];
    int cont = 0;
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "r");
    while (fgets(s, MAXNOME + 1, fich) != NULL) {
        if (strlen(s) >= cont) {
            cont = strlen(s);
            strcpy(nome, s);
        }
    }
    fclose(fich);
    return nome;
}

/*void order_file(FILE *fich) {
    char s[MAXNOME + 1];
    char s1[MAXNOME + 1];
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "r");
    while (fgets(s, MAXNOME + 1, fich) != NULL) {
        while(fgets(s1, MAXNOME + 1, fich)!=NULL){

        }
    }
}

int acrescentar(FILE *fich, char *nome) {
    int cont = 0, num;
    char s[MAXNOME + 1];
    FILE *fich2;
    printf("Em que linha deseja acrescentar? ");
    scanf("%d", &num);
    printf("Que palavra: ");
    get_one_line(nome, MAXNOME + 1);
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "r");
    fich2 = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras1.txt", "w");
    while(fgets(s, MAXNOME + 1, fich) != NULL) {
        cont++;
        if (cont == num) {
            fprintf(fich2, "%s\n", nome);
            fprintf(fich2, "%s", s);
        }
        else fprintf(fich2,"%s\n",s);
    }
    fclose(fich);
    fclose(fich2);
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "w");
    fich2 = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras1.txt", "r");
    while (fgets(s, MAXNOME + 1, fich2) != NULL){
        fprintf(fich,"%s\n",s);
    }
    fclose(fich);
    fclose(fich2);
    return 0;
}

void palindromo(FILE *fich) {
    char s[MAXNOME + 1], s_reverse[MAXNOME + 1];
    int tam;
    FILE *fich2;
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "r");
    fich2 = fopen("C:\\ProgramasPPP\\Problemas_04\\palin.txt", "w");
    while (fgets(s, MAXNOME + 1, fich) != NULL) {
        strcpy(s_reverse, "");
        tam = strlen(s);
        for (int i = 0; i < tam; i++)
            s_reverse[i] = s[tam - i - 1];
        s_reverse[tam] = '\0';
        if (strcasecmp(s_reverse, s) == 0)
            fprintf(fich2, "%s\n", s);
    }
    fclose(fich);
    fclose(fich2);
    return;
}

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

//11.1.8
int main(int argc, char *argv[]) {
    FILE *fich;
    FILE *fich2;
    char c;
    fich = fopen(argv[1], "r");
    fich2 = fopen(argv[2], "w");
    if (argv[0] == "-i") {
        while ((c = getc(fich)) != EOF) {
            if (c == '\r') {
                putc('\n', fich2);
                c = getc(fich);
                if (c == EOF) break;
                if (c == '\n') continue;
            }
            putc(c, fich2);
        }
    } else if (argv[0] == "-o") {
        while ((c = getc(fich)) != EOF) {
            if (c == '\n') {
                putc('\r', fich2);
                putc('\n', fich2);
                c = getc(fich);
                if (c == EOF) break;
                if (c == '\n') continue;
            }
            putc(c, fich2);
        }
    }
    return 0;
}

#define MAXNOME 100

struct pessoa {
    char nome[MAXNOME + 1];
};

void inicializar_arvore(void);

int colocar(struct pessoa alguem);

void juntar_fichs(FILE *fichj);

int get_one_line(FILE *fich, char *linha, int lim);

int main() {
    FILE *fich1 = NULL;
    FILE *fich2 = NULL;
    FILE *fichj = NULL;
    struct pessoa alguem;
    inicializar_arvore();
    fich1 = fopen("C:\\ProgramasPPP\\Problemas_04\\pal1.txt", "r");
    while (get_one_line(fich1, alguem.nome, MAXNOME + 1) != EOF && strcasecmp(alguem.nome, "Fim") != 0) {
        if (colocar(alguem) != 0) {
            fprintf(stderr, "Não há espaço para inserir\n");
            break;
        }
    }
    fclose(fich1);
    fich2 = fopen("C:\\ProgramasPPP\\Problemas_04\\pal2.txt", "r");
    while (get_one_line(fich2, alguem.nome, MAXNOME + 1) != EOF && strcasecmp(alguem.nome, "Fim") != 0) {
        if (colocar(alguem) != 0) {
            fprintf(stderr, "Não há espaço para inserir\n");
            break;
        }
    }
    fclose(fich2);
    fichj = fopen("C:\\ProgramasPPP\\Problemas_04\\paljuntas.txt", "w");
    juntar_fichs(fichj);
    fclose(fichj);
    return 0;
}

struct tnode {
    struct pessoa gente;
    struct tnode *left;      // left child
    struct tnode *right;     // right child
} *raiz;

void inicializar_arvore(void) {
    raiz = NULL;
}

struct tnode *addtree(struct tnode *, struct tnode *);

int colocar(struct pessoa alguem) {
    struct tnode *p;
    p = (struct tnode *) malloc(sizeof(struct tnode)); // make a new node
    if (p == NULL)
        return 1;
    p->gente = alguem;
    p->left = p->right = NULL;
    raiz = addtree(raiz, p);
    return 0;
}

struct tnode *addtree(struct tnode *pr, struct tnode *p) {
    int cond;
    if (pr == NULL) {
        pr = p;
    } else {
        if ((cond = strcasecmp(p->gente.nome, pr->gente.nome)) > 0) {
            pr->right = addtree(pr->right, p);
        } else if (cond < 0)
            pr->left = addtree(pr->left, p);
    }
    return pr;
}

void treeprint(struct tnode *p, FILE *);

void juntar_fichs(FILE *fichj) {
    treeprint(raiz, fichj);
}

void treeprint(struct tnode *p, FILE *fichj) {
    if (p != NULL) {
        treeprint(p->left, fichj);
        fprintf(fichj, "%s\n", p->gente.nome);
        treeprint(p->right, fichj);
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
        if (c == EOF || c == ',')
            return c;
        if (c == '\n')
            break;
        if (!iscntrl(c)) linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);
    return c;
}

#define MAXNOME 100

int get_one_line(char *linha, int lim);

char *size(FILE *, char *);

int acrescentar(FILE *, char *);

void palindromo(FILE *);

int main(void) {
    FILE *fich = NULL;
    char nome[MAXNOME + 1];
    int tamanho = 0;
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "w");
    printf("Insira as plavras que deseja introduzir no ficheiro: ");
    while (get_one_line(nome, MAXNOME + 1) != EOF && strcasecmp(nome, "Fim") != 0)
        fprintf(fich, "%s\n", nome);
    fclose(fich);
    printf("A palavra com o maior número de carateres é: %s", size(fich, nome));
    acrescentar(fich, nome);
    palindromo(fich);
    return 0;
}

char *size(FILE *fich, char *nome) {
    char s[MAXNOME + 1];
    int cont = 0;
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "r");
    while (fgets(s, MAXNOME + 1, fich) != NULL) {
        if (strlen(s) >= cont) {
            cont = strlen(s);
            strcpy(nome, s);
        }
    }
    fclose(fich);
    return nome;
}

void order_file(FILE *fich) {
    char s[MAXNOME + 1];
    char s1[MAXNOME + 1];
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "r");
    while (fgets(s, MAXNOME + 1, fich) != NULL) {
        while(fgets(s1, MAXNOME + 1, fich)!=NULL){

        }
    }
}

int acrescentar(FILE *fich, char *nome) {
    int cont = 0, num;
    char s[MAXNOME + 1];
    FILE *fich2;
    printf("Em que linha deseja acrescentar? ");
    scanf("%d", &num);
    printf("Que palavra: ");
    get_one_line(nome, MAXNOME + 1);
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "r");
    fich2 = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras1.txt", "w");
    while(fgets(s, MAXNOME + 1, fich) != NULL) {
        cont++;
        if (cont == num) {
            fprintf(fich2, "%s\n", nome);
            fprintf(fich2, "%s", s);
        }
        else fprintf(fich2,"%s\n",s);
    }
    fclose(fich);
    fclose(fich2);
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "w");
    fich2 = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras1.txt", "r");
    while (fgets(s, MAXNOME + 1, fich2) != NULL){
        fprintf(fich,"%s\n",s);
    }
    fclose(fich);
    fclose(fich2);
    return 0;
}

void palindromo(FILE *fich) {
    char s[MAXNOME + 1], s_reverse[MAXNOME + 1];
    int tam;
    FILE *fich2=NULL;
    fich = fopen("C:\\ProgramasPPP\\Problemas_04\\palavras.txt", "r");
    fich2 = fopen("C:\\ProgramasPPP\\Problemas_04\\palin.txt", "w");
    while (fgets(s, MAXNOME + 1, fich) != NULL) {
        strcpy(s_reverse, "");
        tam = strlen(s);
        for (int i = 0; i < tam; i++)
            s_reverse[i] = s[tam - i - 1];
        s_reverse[tam] = '\0';
        if (strcasecmp(s_reverse, s) == 0)
            fprintf(fich2, "%s\n", s);
    }
    fclose(fich);
    fclose(fich2);
    return;
}

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
*/
//11.1.2
int main(){
    int num=5;
    int *ptr=&num;
    printf("%d",*ptr);
}
