#include <stdio.h>
#include <string.h>
/*
//8.2.1
static void nova_data(void);

static void listar(void);

static void ordenar(void);

static void vetor_ano(void);

#define MAXDATAS 50
struct datas {
    int dia, mes, ano;
} lista[MAXDATAS];

struct datas_ano {
    int dia, mes, ano;
} lista_ano[MAXDATAS];

int main() {
    int escolha, i;
    for (i = 0; i < MAXDATAS; i++) {
        lista[i].dia = 0;
        lista[i].mes = 0;
        lista[i].ano = 0;
        lista_ano[i].dia = 0;
        lista_ano[i].mes = 0;
        lista_ano[i].ano = 0;
    }
    while (1) {
        printf("\n   0 - Sair\n   1 - Introduzir nova Data\n   2 - Listar Datas\n   3 - Ordenar as Datas\n   4 - Criar vetor com Datas de ano inserido\nEscolha: ");
        if (scanf("%d", &escolha) != 1)
            escolha = -1; // escolha inválida
        while (getchar() != '\n'); //limpar o resto da linha
        if (escolha == 0) return 0;
        if (escolha == 1) nova_data();
        else if (escolha == 2) listar();
        else if (escolha == 3) ordenar();
        else if (escolha == 4) vetor_ano();
        else printf("Escolha inválida\n");
    }

    return 0;
}

void nova_data(void) {
    int i = 0;
    while (i < MAXDATAS && lista[i].dia != 0) {
        i++;
    }
    if (i == MAXDATAS) {
        printf("Não há espaço para mais contactos\n");
        return;
    }
    printf("Introduza a data no formato dia/mes/ano: ");
    scanf("%d/%d/%d", &lista[i].dia, &lista[i].mes, &lista[i].ano);
}

void listar(void) {
    int i;
    if (lista[0].dia == 0) printf("Lista vazia\n");
    else
        for (i = 0; i < MAXDATAS && lista[i].ano != 0; i++) {
            printf("%d/%d/%d\n", lista[i].dia, lista[i].mes, lista[i].ano);
        }
}

void ordenar(void) {
    int cont = 0, flag = 0;
    if (lista[cont].dia == 0) printf("Lista Vazia.");
    while (cont < MAXDATAS && lista[cont].dia != 0) cont++;
    for (int i = 0; i < cont; i++)
        for (int j = 0; j < cont - 1; j++) {
            if (lista[j].ano > lista[j + 1].ano) {
                flag = lista[j].ano;
                lista[j].ano = lista[j + 1].ano;
                lista[j + 1].ano = flag;
                flag = lista[j].mes;
                lista[j].mes = lista[j + 1].mes;
                lista[j + 1].mes = flag;
                flag = lista[j].dia;
                lista[j].dia = lista[j + 1].dia;
                lista[j + 1].dia = flag;
            }
            if (lista[j].ano == lista[j + 1].ano && lista[j].mes > lista[j + 1].mes) {
                flag = lista[j].ano;
                lista[j].ano = lista[j + 1].ano;
                lista[j + 1].ano = flag;
                flag = lista[j].mes;
                lista[j].mes = lista[j + 1].mes;
                lista[j + 1].mes = flag;
                flag = lista[j].dia;
                lista[j].dia = lista[j + 1].dia;
                lista[j + 1].dia = flag;
            }
            if (lista[j].ano == lista[j + 1].ano && lista[j].mes == lista[j + 1].mes &&
                lista[j].dia > lista[j + 1].dia) {
                flag = lista[j].ano;
                lista[j].ano = lista[j + 1].ano;
                lista[j + 1].ano = flag;
                flag = lista[j].mes;
                lista[j].mes = lista[j + 1].mes;
                lista[j + 1].mes = flag;
                flag = lista[j].dia;
                lista[j].dia = lista[j + 1].dia;
                lista[j + 1].dia = flag;
            }
        }
}

static void vetor_ano(void) {
    int n, cont = 0, i=0, cont_vetor=0;
    printf("Insira o ano: ");
    scanf("%d", &n);
    while (cont < MAXDATAS && lista[cont].dia != 0) cont++;
    for (int i = 0; i < cont; i++)
        if (lista[i].ano == n) {
            lista_ano[cont_vetor].ano = lista[i].ano;
            lista_ano[cont_vetor].mes = lista[i].mes;
            lista_ano[cont_vetor].dia = lista[i].dia;
            cont_vetor++;
        }
    if (lista_ano[0].ano == 0) printf("Lista vazia\n");
    else
        for (i = 0; i < MAXDATAS && lista_ano[i].ano != 0; i++) {
            printf("%d/%d/%d\n", lista_ano[i].dia, lista_ano[i].mes, lista_ano[i].ano);
        }
}

//9.1.1 (Lista Circular)
#define MAX 10
#define TAMMAX 10

struct lista_num {
    char txt;
    char num;
} lista[TAMMAX];

int prim_vazio;
int prim_mens;

int adiciona(char numeros[TAMMAX], int i);

int main() {
    int i;
    for (i = 0; i < TAMMAX; i++) {
        lista[i].txt = 0;
        lista[i].num = 0;
    }
    char numeros[TAMMAX] = {'1', '2', '3', '4', '5', '6', '7', '0', '8'};
    prim_vazio = TAMMAX - 1;
    prim_mens = TAMMAX - 1;
    for (i = 0; i < TAMMAX; i++) {
        if (numeros[i] != 0 && adiciona(numeros, i) != 0) {
            printf("Colocação com erro.\n");
        }
    }
    for (i = 0; i < TAMMAX; i++) {
        if (lista[i].txt != 0) {
            printf("%d\t", lista[i].num);
        }
    }
    return 0;
}

int adiciona(char numeros[TAMMAX], int i) {
    if (prim_mens != prim_vazio || lista[prim_vazio].txt == 0) {
        lista[prim_vazio].num = numeros[i] - '0';
        lista[prim_vazio].txt = 1;
        prim_vazio--;
        return 0;
    } else {
        return 1;
    }
}

//9.1.1 (Lista Ligada)
#define MAX 10
#define TAMMAX 10

int entrada_lista;

struct lista_num {
    char txt;
    char num;
} lista[TAMMAX];

struct elem_fila {
    struct lista_num numeros;
    int first_send;
    int next_send;
} fila[TAMMAX];


int adiciona(char numeros[TAMMAX]);

int main() {
    int i;
    for (i = 0; i < TAMMAX; i++) {
        lista[i].txt = 0;
        lista[i].num = 0;
    }
    for (i = 0; i < TAMMAX; i++)
        fila[i].first_send = -1;
    char numeros[TAMMAX] = {'1', '2', '3', '4', '5', '6', '7', '0', '8'};
    entrada_lista = -1;
    for (i = 0; i < TAMMAX; i++) {
        if (numeros[i] != 0 && adiciona(numeros) != 0) {
            printf("Colocação com erro.\n");
        }
    }
    for (i = 0; i < TAMMAX; i++) {
        if (lista[i].txt != 0) {
            printf("%d\t", lista[i].num);
        }
    }
    return 0;
}

int adiciona(char numeros[TAMMAX]) {
    int i, anterior, prox;
    for (i = 0; i < TAMMAX && fila[i].first_send >= 0; i++);
    if (i >= TAMMAX) return 1;
    if (entrada_lista < 0) {
        entrada_lista = i;
        fila[i].next_send = -1;
    }
    fila[i].first_send = numeros;
    fila[i].first_send = first_send;
}

//Ex 9.1.3
#define MAX 10

struct numero {
    int num;
    int next;       //para onde saltar
    int prev;       // de onde saltou
} lista[MAX];

int entrada_lista;
int saida_lista;

int add(int num_add);

int max();

int min();

float media();

int main() {
    int i, n, m;
    float k;
    entrada_lista = -1;
    saida_lista = -1;
    for (i = 0; i < MAX; i++) {
        lista[i].num = -1;
        lista[i].next = -1;
    }
    for (n = 0; n < 5; n++) {
        m = n * 4 + 2;
        if (add(m) == 1) {
            printf("Lista está cheia\n");
            return 0;
        }
    }
    if (add(4) == 1) {
        printf("Lista está cheia\n");
        return 0;
    }
    for (i = entrada_lista; lista[i].next != -1; i = lista[i].next) {       //segue os endereços
        if (lista[i].num != -1) {
            printf("'%d'-", lista[i].num);
        }
    }
    printf("#%d#\n", max());
    printf("#%d#\n", min());
    if ((k = media()) != -1) {
        printf("#%.4f#\n", k);
    } else {
        printf("Lista está cheia\n");
    }
    return 0;
}

int add(int num_add) {
    int i, anterior, prox;
    for (i = 0; i < MAX && lista[i].num >= 0; i++);
    if (i == MAX) {
        return 1; //lista cheia
    }
    lista[i].num = num_add;
    if (entrada_lista < 0) {      //lista vazia
        entrada_lista = i;
        saida_lista = i;
        lista[i].prev = -1;
        lista[i].next = -1;
    } else {        // tem numeros
        if (num_add <= lista[entrada_lista].num) {
            lista[i].prev = -1;
            lista[entrada_lista].next = i;
            lista[i].next = entrada_lista;
            entrada_lista = i;
        } else {
            anterior = entrada_lista;
            prox = lista[entrada_lista].next;
            while (prox >= 0 && lista[prox].num < num_add) {
                anterior = prox;
                prox = lista[prox].next;
            }
            if (prox < 0) {       //final da lista
                lista[anterior].next = i;
                lista[i].next = -1;
                lista[i].prev = anterior;
                saida_lista = i;
            } else {     //inserir no meio
                lista[anterior].next = i;
                lista[i].prev = anterior;
                lista[i].next = prox;
                lista[prox].prev = i;
            }
        }
    }
    return 0;
}

int max() {
    int i;
    for (i = entrada_lista; lista[i].next != -1; i = lista[i].next);
    return lista[i].num;
}

int min() {
    int i;
    for (i = saida_lista; lista[i].prev != -1; i = lista[i].prev);
    return lista[i].num;
}

float media() {
    int med = 0, count = 0, i;
    float res;
    for (i = entrada_lista; lista[i].next != -1; i = lista[i].next) {
        med += lista[i].num;
        count++;
    }
    med += lista[i].num;
    count++;
    if (count > 0) {
        res = (float) med / (float) count;
    } else {
        return -1;
    }
    return res;
}
//9.2.2 (Lista Ligada)
#define MAX 10

struct numero {
    char data[11];
    int next;       //para onde saltar
    int prev;       // de onde saltou
} lista[MAX];

int entrada_lista;
int saida_lista;

int add(char date[11]);

int invert();

int main() {
    int i, n, m;
    char date1[11] = "11/05/2000", date2[11] = "20/10/2005", date3[11] = "09/06/2001";
    entrada_lista = -1;
    saida_lista = -1;

    for (i = 0; i < MAX; i++) {
        lista[i].data[0] = 'a';
        lista[i].next = -1;
        lista[i].prev = -1;
    }


    if (add(date1) == 1) {
        printf("Lista está cheia\n");
        //return 0;
    }
    if (add(date2) == 1) {
        printf("Lista está cheia\n");
    }
    if (add(date3) == 1) {
        printf("Lista está cheia\n");
    }


    for (i = 0; i < MAX; i++) {     //imprime a lista
        if (lista[i].data[0] != 'a') {
            printf("%s-", lista[i].data);
        }
    }
    printf("#\n");

    invert();

    return 0;
}


int add(char date[11]) {
    int i, m, anterior, prox;

    for (i = 0; i < MAX && lista[i].data[0] != 'a'; i++);
    if (i == MAX) {
        return 1; //lista cheia
    }
    for (m = 0; m < 11; m++) {
        lista[i].data[m] = date[m];
    }
    if (entrada_lista < 0) {      //lista vazia
        entrada_lista = i;
        saida_lista = i;
        lista[i].prev = -1;
        lista[i].next = -1;
    } else {        // tem numeros
        anterior = entrada_lista;
        prox = lista[entrada_lista].next;
        while (prox >= 0) {
            anterior = prox;
            prox = lista[prox].next;
        }
        if (prox < 0) {       //final da lista
            lista[anterior].next = i;
            lista[i].next = -1;
            lista[i].prev = anterior;
            saida_lista = i;
        } else {     //inserir no meio
            lista[anterior].next = i;
            lista[i].prev = anterior;
            lista[i].next = prox;
            lista[prox].prev = i;

        }

    }


    return 0;

}

int invert() {
    int i, n, c = 0;

    for (i = saida_lista; lista[i].prev != -1; i = lista[i].next) {
        lista[i].next = n;
        lista[i].next = lista[i].prev;
        lista[i].prev = n;
        if (lista[i].data != 'a') {
            printf("%s-", lista[i].data);
        }
    }
    lista[i].next = n;
    lista[i].next = lista[i].prev;
    lista[i].prev = n;
    if (lista[i].data != 'a') {
        printf("%s-", lista[i].data);
    }

    return 0;
}

//9.2.2 (Lista Duplamente Ligada)
#define MAX 10

struct numero {
    char data[11];
    int next;       //para onde saltar
    int prev;       // de onde saltou
} lista[MAX];

int entrada_lista;
int saida_lista;

int add(char date[11]);

int invert();

int main() {
    int i, n, m;
    char date1[11] = "11/05/2000", date2[11] = "20/10/2005", date3[11] = "09/06/2001";
    entrada_lista = -1;
    saida_lista = -1;
    for (i = 0; i < MAX; i++) {
        lista[i].data[0] = 'a';
        lista[i].next = -1;
        lista[i].prev = -1;
    }
    if (add(date1) == 1) {
        printf("Lista está cheia\n");
        //return 0;
    }
    if (add(date2) == 1) {
        printf("Lista está cheia\n");
    }
    if (add(date3) == 1) {
        printf("Lista está cheia\n");
    }
    for (i = 0; i < MAX; i++) {     //imprime a lista
        if (lista[i].data[0] != 'a') {
            printf("%s\t", lista[i].data);
        }
    }
    printf("\n");
    invert();
    return 0;
}
int add(char date[11]) {
    int i, m, anterior, prox;

    for (i = 0; i < MAX && lista[i].data[0] != 'a'; i++);
    if (i == MAX) {
        return 1; //lista cheia
    }
    for (m = 0; m < 11; m++) {
        lista[i].data[m] = date[m];
    }
    if (entrada_lista < 0) {      //lista vazia
        entrada_lista = i;
        saida_lista = i;
        lista[i].prev = -1;
        lista[i].next = -1;
    } else {        // tem numeros
        anterior = entrada_lista;
        prox = lista[entrada_lista].next;
        while (prox >= 0) {
            anterior = prox;
            prox = lista[prox].next;
        }
        if (prox < 0) {       //final da lista
            lista[anterior].next = i;
            lista[i].next = -1;
            lista[i].prev = anterior;
            saida_lista = i;
        } else {     //inserir no meio
            lista[anterior].next = i;
            lista[i].prev = anterior;
            lista[i].next = prox;
            lista[prox].prev = i;
        }
    }
    return 0;
}

int invert() {
    int i, n, c = 0;
    for (i = saida_lista; lista[i].prev != -1; i = lista[i].next) {
        lista[i].next = n;
        lista[i].next = lista[i].prev;
        lista[i].prev = n;
        if (lista[i].data != 'a') {
            printf("%s\t", lista[i].data);
        }
    }
    lista[i].next = n;
    lista[i].next = lista[i].prev;
    lista[i].prev = n;
    if (lista[i].data != 'a') {
        printf("%s\t", lista[i].data);
    }

    return 0;
}

//9.1.4
#define MAX 10
#define MAXSTRING 50
struct strings {
    char cadeias[MAXSTRING];
    int next;       //para onde saltar
    int prev;       // de onde saltou
} lista[MAX];

int entrada_lista;
int saida_lista;

int add(char string[MAXSTRING]);

const char *retirar(void);

int main() {
    int i, n, m, cont = 0, tam_cad = 0;
    char cad_max[MAXSTRING], cad[MAXSTRING];
    char string1[MAXSTRING] = "Eu sou o joao", string2[MAXSTRING] = "Eu estava ali a passear e fui buscar uma cena fixe", string3[MAXSTRING] = "Que e que tu queres";
    entrada_lista = -1;
    saida_lista = -1;
    for (i = 0; i < MAX; i++) {
        lista[i].cadeias[0] = 'a';
        lista[i].next = -1;
        lista[i].prev = -1;
    }
    if (add(string1) == 1) printf("Lista está cheia.\n");
    if (add(string2) == 1) printf("Lista está cheia.\n");
    if (add(string3) == 1) printf("Lista está cheia.\n");
    printf("A lista é: \n");
    for (i = 0; i < MAX; i++) { //imprime a lista
        if (lista[i].cadeias[0] != 'a') {
            printf("-> %s\n", lista[i].cadeias);
        }
    }
    for (int x = i; x > 0; x--) {
        strcpy(cad, retirar());
        if (cad[0] != '\0') {
            cont++;
            if (tam_cad < strlen(cad)) {
                tam_cad = strlen(cad);
                strcpy(cad_max, cad);
            }
        }
    }
    printf("Foram lidas %d cadeias strings e a maior string é \"%s\".", cont, cad_max);
    return 0;
}


int add(char string[MAXSTRING]) {
    int i, m, anterior, prox;

    for (i = 0; i < MAX && lista[i].cadeias[0] != 'a'; i++);
    if (i == MAX) {
        return 1; //lista cheia
    }
    for (m = 0; m < MAXSTRING; m++) {
        lista[i].cadeias[m] = string[m];
    }
    if (entrada_lista < 0) {      //lista vazia
        entrada_lista = i;
        saida_lista = i;
        lista[i].prev = -1;
        lista[i].next = -1;
    } else {        // tem numeros
        anterior = entrada_lista;
        prox = lista[entrada_lista].next;
        while (prox >= 0) {
            anterior = prox;
            prox = lista[prox].next;
        }
        if (prox < 0) {       //final da lista
            lista[anterior].next = i;
            lista[i].next = -1;
            lista[i].prev = anterior;
            saida_lista = i;
        } else {     //inserir no meio
            lista[anterior].next = i;
            lista[i].prev = anterior;
            lista[i].next = prox;
            lista[prox].prev = i;
        }
    }
    return 0;
}

const char *retirar(void) {
    int i, j;
    if (entrada_lista < 0) {
        // lista vazia
        lista[0].cadeias[0] = 0;
        return lista[0].cadeias;
    }
    //  Procurar a última mensagem da lista
    j = -1;
    for (i = entrada_lista; lista[i].next != -1; i = lista[i].next)
        j = i; // guardar a localização da mensagem anterior à que vai sair
    if (j == -1) {
        //só havia uma mensagem na fila - vai ficar vazia
        entrada_lista = -1;
    } else {
        // havia mais do que uma mensagem na lista
        lista[j].next = -1;
    }
    return lista[i].cadeias;
}

//9.1.5
#define MAX 10
struct numbers {
    double numero;
} lista[MAX];

int prim_vazia;
int prim_numero;
double primeiro;

int add(double random);

double retirar(void);

int main() {
    int i;
    double random = 1.2367512;
    prim_vazia = MAX - 1;
    prim_numero = MAX - 1;
    for (i = 0; i < MAX; i++) lista[i].numero = 0;
    while (add(random) != 1) {
        random += 1.1;
        random *= 2.1;
    }
    for (int n = 0; n < MAX; n++) printf("%f\n", lista[n].numero);
    for (int n = 0; n < MAX; n++) {
        retirar();
    }
    for (int n = 0; n < MAX; n++) printf("%f\n", lista[n].numero);
    return 0;
}

int add(double random) {
    if (prim_vazia != prim_numero || lista[prim_numero].numero == 0) {
        lista[prim_vazia].numero = random;
        prim_vazia--;
        if (prim_vazia < 0) prim_vazia = MAX - 1;
        return 0;
    } else
        return 1;
}

double retirar(void) {
    primeiro = lista[prim_numero].numero;
    if (prim_numero != prim_vazia || lista[prim_numero].numero != 0) {
        lista[prim_numero].numero = 0;
        prim_numero--;
        if (prim_numero < 0) prim_numero = MAX - 1;
    }
    return primeiro;
}


#define MAX 10
struct numeros {
    int num;
    int next;       //para onde saltar
    int prev;       // de onde saltou
} lista[MAX];

int entrada_lista;
int saida_lista;
int soma = 0;

int add(int n);

int retirar(void);

int soma_recursiva(void);

int main() {
    int i, n = 1, m, cont = 0;
    entrada_lista = -1;
    saida_lista = -1;
    for (i = 0; i < MAX; i++) {
        lista[i].num = 0;
        lista[i].next = -1;
        lista[i].prev = -1;
    }
    for (i = 0; i < MAX; i++) {
        cont++;
        add(cont * n);
    }
    printf("A lista é: \n");
    for (i = 0; i < MAX; i++) { //imprime a lista
        if (lista[i].num != 0) {
            printf("%d\t", lista[i].num);
        }
    }
    soma_recursiva();
    printf("\nA soma de todos os numeros é %d.", soma);
    return 0;
}


int add(int n) {
    int i, m, anterior, prox;
    for (i = 0; i < MAX && lista[i].num != 0; i++);
    if (i == MAX) {
        return 1; //lista cheia
    }
    lista[i].num = n;
    if (entrada_lista < 0) {      //lista vazia
        entrada_lista = i;
        saida_lista = i;
        lista[i].prev = -1;
        lista[i].next = -1;
    } else {        // tem numeros
        anterior = entrada_lista;
        prox = lista[entrada_lista].next;
        while (prox >= 0) {
            anterior = prox;
            prox = lista[prox].next;
        }
        if (prox < 0) {       //final da lista
            lista[anterior].next = i;
            lista[i].next = -1;
            lista[i].prev = anterior;
            saida_lista = i;
        } else {     //inserir no meio
            lista[anterior].next = i;
            lista[i].prev = anterior;
            lista[i].next = prox;
            lista[prox].prev = i;
        }
    }
    return 0;
}

int retirar(void) {
    int i, j;
    if (entrada_lista < 0) {
        // lista vazia
        lista[0].num = 0;
        return lista[0].num;
    }
    //  Procurar a última mensagem da lista
    j = -1;
    for (i = entrada_lista; lista[i].next != -1; i = lista[i].next)
        j = i; // guardar a localização da mensagem anterior à que vai sair
    if (j == -1) {
        //só havia uma mensagem na fila - vai ficar vazia
        entrada_lista = -1;
    } else {
        // havia mais do que uma mensagem na lista
        lista[j].next = -1;
    }
    return lista[i].num;
}

int soma_recursiva(void) {
    int cont = 0;
    cont = retirar();
    if (cont != 0) {
        soma += cont;
        return soma_recursiva();
    } else return 0;
}

//9.1.6
#include <stdio.h>

struct n {
    long double numeros;
};
// dev ser sempre chamada antes da fila ser usada
void inicializar_fila(void);

// coloca uma mensagem na fila. Devolve zero se tudo correu bem, devolve 1 se não havia espaço disponível
int colocar(long double num);

// devolve a mensagem que estava à saída da fila. Se a fila estava vazia, devolve 1 em *pvazio; se havia pelo menos uma mensagem na fila,
//         devolve zero em *pvazio
long double retirar(int *pvazio);

int main() {
    // programa simples para testar a fila
    int i, vazio;
    inicializar_fila();
    struct n n1 = {652.61};
    if (colocar(n1.numeros) != 0)
        printf("Erro na colocação\n ");
    else
        printf("Colocação com sucesso\n");
    return 0;
}

// lista ligada construída com memória dinâmica

#include <stdlib.h>

struct elem_fila {
    long double num;
    struct elem_fila *num_seguinte;
};

// Ponteiro para o primeiro elemento da fila; = NULL se lista vazia
static struct elem_fila *raiz;
long double num_vazio = 0;

void inicializar_fila(void) {
    raiz = NULL;
}

int colocar(long double num) {
    struct elem_fila *aux;
    //Obter espaço para um novo nó
    aux = (struct elem_fila *) malloc(sizeof(struct elem_fila));
    if (aux == NULL)
        //não há espaço
        return 1;

    // inserir à entrada da lista
    aux->num = num;
    aux->num_seguinte = raiz;
    raiz = aux;
    return 0;
}

long double retirar(int *pvazio) {
    struct elem_fila *prox, *anterior;
    long double num;

    if (raiz == NULL) {
        // lista vazia
        *pvazio = 1;
        return num_vazio;
    }

    *pvazio = 0;

    //  Procurar a última mensagem da lista
    anterior = NULL;
    for (prox = raiz; prox->num_seguinte != NULL; prox = prox->num_seguinte)
        anterior = prox; // guardar a localização da mensagem anterior à que vai sair

    if (anterior == NULL) {
        //só havia uma mensagem na fila - vai ficar vazia
        num = raiz->num;
        free(raiz);
        raiz = NULL;
    } else {
        // havia mais do que uma mensagem na lista
        anterior->num_seguinte = NULL;
        num = prox->num;
        free(prox);
    }
    return num;
}

//9.1.8
#include <stdio.h>
#include <stdlib.h>  // for atof()
#include <ctype.h>
#define MAXOP 50    // max size of operand or operator
   // signal that a number was found

const char * getop();

// interface genérico da pilha
// inicializar a pilha
void inicializar_pilha(void);

// coloca uma número na pilha. Devolve zero se tudo correu bem, devolve 1 se não havia espaço disponível
int push(char str[50] );

// devolve o número que estava no topo da pilha. Se a pilha estava vazia, devolve 1 em *pvazio; se havia pelo menos um número na pilha,
//         devolve zero em *pvazio
void pop(int *pvazio, char str[50]);



int main(void) {
    int type;
    double op2;
    char s[MAXOP], c1[MAXOP];
    int v1, v2,c, i=0;
    while ((c=getchar())!=EOF && c!='\n') {
        s[i] = c;
        i++;
    }
    if(push(s)!=0) printf("Colocação falahada!");
    else printf("Colocação com sucesso!");
    return 0;
}


// secção onde a pilha é implementada

static struct no_pilha {
    char string[50];
    struct no_pilha *pseg;
} *raiz; //stack pointer

// inicializar a pilha
void inicializar_pilha(void) {
    raiz = NULL;
};

// coloca uma número na pilha. Devolve zero se tudo correu bem, devolve 1 se não havia espaço disponível
int push(char str[50]) {
    struct no_pilha *aux;

    //Obter espaço para um novo nó
    aux = (struct no_pilha *) malloc(sizeof(struct no_pilha));
    if (aux == NULL)
        //não há espaço
        return 1;

    // inserir à entrada da lista
    strcpy(aux->string,str);
    aux->pseg = raiz;
    raiz = aux;
    return 0;
}

// devolve o número que estava no topo da pilha. Se a pilha estava vazia, devolve 1 em *pvazio; se havia pelo menos um número na pilha,
//         devolve zero em *pvazio
void pop(int *pvazio, char str[50]) {
    struct no_pilha *aux;

    if (raiz == NULL) {
        // lista vazia
        *pvazio = 1;
        return;
    }

    *pvazio = 0;

    //  Retirar o dado à entrada da lista
    strcpy(str,raiz->string);
    aux = raiz->pseg;
    free(raiz);
    raiz = aux;
    return;
}

//*********************************************************
// section with input character functions


int getch(void);

void ungetch(int);




#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free position in buf

int getch(void)      // get a (possibly pushed back) character
{
    int c;
    if (bufp > 0)
        c = buf[--bufp];
    else
        c = getchar();
    return c;
}

void ungetch(int c)  // push back on input
{
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

//Ex 10.1
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


int main(void) {
    struct tnode *root;
    char word[MAXWORD];
    int num, n_estudante, ano;
    root = NULL;
    while (1) {
        printf("0 - Sair.\n1 - Adicionar Aluno.\n2 - Visualizar lista de alunos.\nEscolha: ");
        scanf(" %d", &num);
        if (num == 1) root = addtree(root, word, n_estudante, ano);
        else if (num == 2) treeprint(root);
        else if (num == 0) break;
    }
    return 0;

}

struct tnode *talloc(void);

char *stringdup(char *);


struct tnode *addtree(struct tnode *p, char *w, int n_estudante, int ano) {
    int cond, n;
    printf("Deseja sair? (1-Sim/0-Não): ");
    scanf("%d", &n);
    if (n == 1) return p;
    printf("Nome Estudante: ");
    getword(w, MAXWORD);
    if (isalpha(w[0])) {
        printf("Nº Estudante: ");
        scanf("%d", &n_estudante);
        printf("Ano: ");
        scanf("%d", &ano);
    }
    if (p == NULL)               // a new word has arrived
    {
        p = talloc();            // make a new node
        p->word = stringdup(w);
        p->n_estudante = n_estudante;
        p->ano = ano;
        p->left = p->right = NULL;
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
        treeprint(p->right);
        printf("%4d - %s - %d\n", p->ano, p->word, p->n_estudante);
        treeprint(p->left);
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


int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()));
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free posotion in buf

int getch(void)      // get a (possibly pushed back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  // push back on input
{
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else buf[bufp++] = c;
}
*/
// 10.1.3
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXNOME 100

struct pessoa {
    char nome[MAXNOME + 1];
    unsigned int ano_nasc;
};

// deve ser sempre chamada antes da árvore ser usada
void inicializar_arvore(void);

// coloca uma pessoa na árvore. Devolve zero se tudo correu bem, devolve 1 se não havia espaço disponível
int colocar(struct pessoa alguem);

int retirar(char nome[]);

// obter o ano de nascimento de alguém. Ignora diferença entre maiúsculas e minúsculas.
// Devolve zero se a pessoa não foi encontrada
unsigned int consultar(char nome[]);

// obter os dados da próxima pessoa (por ordem alfabética) presente na árvore, a seguir ao nome indicado
// Se não há ninguém na árvore com um nome a seguir ao fornecido, devolve 1 em *pvazio;
// se havia pelo menos mais uma pessoa na árvore, devolve zero em *pvazio
struct pessoa seguinte(int *pvazio, const char nome[MAXNOME + 1]);

void mostrar_tudo(void);

/*****************************************************/

int get_one_line(char *linha, int lim);


int main(void) {

    char ano_str[10];
    struct pessoa alguem;
    unsigned int ano;
    int vazio, cont = 0, num, n;
    inicializar_arvore();
    while (1) {
        printf("0 - Sair\n1 - Adicionar pessoas\n2 - Consultar ano de nascimento\n3 - Varrimento a partir de nome\n4 - "
               "Eliminar pessoa\n5 - Agrupar pelo 1º nome\n6 - Contar o nº de  elementos\n7 - Imprimir dados\nEscolha: ");
        scanf("%d", &n);
        if (n == 1) {
            while (get_one_line(alguem.nome, MAXNOME + 1) != EOF && strcasecmp(alguem.nome, "Fim") != 0) {
                if (get_one_line(ano_str, 6) != EOF) {
                    alguem.ano_nasc = (unsigned int) strtol(ano_str, NULL, 0);
                    if (colocar(alguem) != 0) {
                        printf("Não há espaço para inserir\n");
                        break;
                    }
                }
            }
        } else if (n == 2) {
            strcpy(alguem.nome, "");
            while (strcasecmp(alguem.nome, "FIM") != 0) {
                printf("Nome da pessoa a procurar? ");
                get_one_line(alguem.nome, MAXNOME + 1);
                if ((ano = consultar(alguem.nome)) > 0)
                    printf("Ano nascimento %u\n", ano);
                else
                    printf("Não existe\n");
            }
        } else if (n == 3) {
            printf("Nome da pessoa inicial do varrimento? ");
            get_one_line(alguem.nome, MAXNOME + 1);
            while (strcasecmp(alguem.nome, "FIM") != 0) {
                alguem = seguinte(&vazio, alguem.nome);
                while (!vazio) {
                    printf("%4u %s\n", alguem.ano_nasc, alguem.nome);
                    alguem = seguinte(&vazio, alguem.nome);
                }
                printf("Nome da pessoa inicial do varrimento? ");
                get_one_line(alguem.nome, MAXNOME + 1);
            }
        } else if (n == 4) {
            strcpy(alguem.nome, "");
            while (strcasecmp(alguem.nome, "FIM") != 0) {
                printf("Nome da pessoa a eliminar? ");
                get_one_line(alguem.nome, MAXNOME + 1);
                if ((num = retirar(alguem.nome)) == 0)
                    printf("Retirado com sucesso.\n");
                else
                    printf("Erro. Não retirado ou nome inexistente.\n");
            }
        } else if (n == 5) {
            strcpy(alguem.nome, " ");
            alguem = seguinte(&vazio, alguem.nome);
            while (!vazio) {
                printf("%4u %s\n", alguem.ano_nasc, alguem.nome);
                alguem = seguinte(&vazio, alguem.nome);
            }
        } else if (n == 6) {
            strcpy(alguem.nome, " ");
            alguem = seguinte(&vazio, alguem.nome);
            while (!vazio) {
                alguem = seguinte(&vazio, alguem.nome);
                cont++;
            }
            printf("\nA árvore binária tem %d elementos.\n", cont);
        } else if (n == 7) mostrar_tudo();
        else return 0;
    }
}

struct tnode               // the tree node:
{
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

struct tnode *find(struct tnode *pr, char *pn);

int retirar(char nome[]) {
    struct tnode *p;
    p = find(raiz, nome);
    if (p == NULL)
        return 1;
    else {
        strcpy(p->gente.nome, "");
        p->gente.ano_nasc = 0;
        p = NULL;

    }
    return 0;
}

unsigned int consultar(char nome[]) {
    struct tnode *p;
    p = find(raiz, nome);
    if (p == NULL)
        return 0;
    else
        return p->gente.ano_nasc;
}

struct tnode *find(struct tnode *pr, char *pn) {
    int cond;
    if (pr == NULL)
        return NULL;
    else if ((cond = strcasecmp(pr->gente.nome, pn)) == 0)
        return pr;
    else if (cond > 0)
        return find(pr->left, pn);
    return find(pr->right, pn);
}

struct tnode *find_next(struct tnode *pr, const char *anterior, struct tnode *candidato);

struct pessoa pes_vazia = {"", 0};

struct pessoa seguinte(int *pvazio, const char nome[MAXNOME + 1]) {
    struct tnode *p;
    p = find_next(raiz, nome, NULL);
    if (p == NULL) {
        *pvazio = 1;
        return pes_vazia;
    }
    *pvazio = 0;
    return p->gente;
}

// devolve NULL se não há seguinte
struct tnode *find_next(struct tnode *pr, const char *anterior, struct tnode *candidato) {
    int cond;
    if (pr == NULL) return candidato;
    if ((cond = strcasecmp(anterior, pr->gente.nome)) >= 0)
        return find_next(pr->right, anterior, candidato);
    else
        return find_next(pr->left, anterior, pr);
}

void treeprint(struct tnode *p);

void mostrar_tudo(void) {
    treeprint(raiz);
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4u %s\n", p->gente.ano_nasc, p->gente.nome);
        treeprint(p->right);
    }
}

/* get next line from input - "lim" includes the terminating zero */
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