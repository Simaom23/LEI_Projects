#include <stdio.h>
#include <locale.h>
#include <ctype.h>
/*
//5.1.1
#define true 1
#define false 0
int main() {
    float fahr, celsius;
    float *point_fahr, *point_celsius;
    int lower, upper, step, *point_step, *point_upper;
    point_celsius = &celsius;
    point_step = &step;
    point_upper = &upper;
    point_fahr = &fahr;
    lower = 0;
    upper = 300;
    step = 20;
    fahr = lower;
    while (true) {
        *point_celsius = (5.0 / 9.0) * (*point_fahr - 32);
        printf("%3.0f %6.1f\n", *point_fahr, *point_celsius);
        *point_fahr += *point_step;
        if (fahr > *point_upper) break;
    }
    return 0;
}

//Ex 5.2.1
static int h[5] = {0, 0, 0, 0, 0};

int media_pesada(void) {
    int j, res;
    for (j = 4; j > 0; j--) h[j] = h[j - 1];
    h[0] = i;
    res = (5 * h[0] + 4 * h[1] + 3 * h[2] + 2 * h[3] + 1 * h[4]) / 15;
    return res;
}

int media_simples(void) {
    int j, res;
    for (j = 4; j > 0; j--) h[j] = h[j - 1];
    h[0] = i;
    res = (h[0] + h[1] + h[2] + h[3] + h[4]) / 5;
    return res;
}

int main(void) {
    int i, t;
    printf("Tipo de filtro ? (1- média simples, 2- média pesada) ");
    scanf("%d", &t);
    if (t != 1 && t != 2) return 1;
    while (1) {
        printf("Número ? ");
        scanf("%d", &i);
        if (i < 0) break;
        if (t == 2) printf("Média pesada %d\n", media_pesada()); else printf("Média simples %d\n", media_simples());
    }
    return 0;
}

//Ex 6.1.1
int main() {
    int n, n_primo = 1, cont = 0, cont_div = 0;
    printf("Introduza o tamanho do vetor: ");
    scanf("%d", &n);
    int vetor[100];
    while (cont != n) {
        for (int i = 1; i <= n_primo; i++) {
            if (cont_div == n_primo ) {
                vetor[cont] = n_primo;
                printf("%d, ", vetor[cont]);
                cont++;
                n_primo++;
            } else if (n_primo % i != 0) cont_div++;
        }
    }
    return 0;
}

//Ex 6.1.2
int main() {
    int vetor[9], vetor_invertido[9];
    for (int i = 0; i < 10; i++) {
        printf("Introduza o inteiro no espaço %d do vetor: ", i + 1);
        scanf("%d", &vetor[i]);
    }
    printf("A matriz invertida é: ");
    for (int i = 0; i < 10; i++) {
        vetor_invertido[i] = vetor[10 - i - 1];
        printf("%d\t", vetor_invertido[i]);
    }
    return 0;
}

//Ex 6.1.3
int main() {
    int v1[10], v2[10], vt[20], flag = 0, cont = 0;
    while (cont != 10) {
        printf("Introduza valor para V1: ");
        scanf("%d", &v1[cont]);
        if (v1[cont] == "\n") break;
        cont++;
    }
    for (char i = 0; i <= cont - 1; i++) {
        for (char j = 0; j <= cont - 1; j++)
            if (v1[i] < v1[j]) {
                flag = v1[i];
                v1[i] = v1[j];
                v1[j] = flag;
            }
    }
    cont = 0;
    printf("\n");
    while (cont != 10) {
        printf("Introduza valor para V2: ");
        scanf("%d", &v2[cont]);
        if (v2[cont] == "\n") break;
        cont++;
    }
    for (char i = 0; i <= cont - 1; i++) {
        for (char j = 0; j <= cont - 1; j++)
            if (v2[i] < v2[j]) {
                flag = v2[i];
                v2[i] = v2[j];
                v2[j] = flag;
            }
    }

double soma_vetores() {
    double va[5], vb[5], vc[5];
    printf("Introduza o vetor a: ");
    for (char i = 0; i <= 5; i++) {
        printf("Introduza o vetor a: ");
        scanf("%d", &va[i]);
    }
    for (char i = 0; i <= 5; i++) {
        printf("Introduza o vetor b: ");
        scanf("%d", &vb[i]);
    }
    for (char i = 0; i <= 5; i++){
        vc[i]=vb[i]+va[i];
        printf("%f",vc[i]);
    }
}

int main() {
    soma_vetores();
    return 0;
}

//Ex 7.1.1
int main() {
    int i=0;
    printf("Introduza a string:\n");
    i = getString();
    printf("Tem %d palavras.", i);
}
int getString() {
    int lim = 60, cont = 1, c1 = 0, c = 0;
    for (char i = 0; i < lim - 1 && (c = getchar())!='\n'; i++) {
        if (c == ' ' &&  c1!=' ') cont++;
        c1=c;
    }
    return cont;
}

//7.1.1 (UTF-8)
int main() {
    char s[]="eu estou aqui ç";
    printf("%lu", strlen_u8(s));
    return 0;
}

size_t strlen_u8(const char *s) {
    size_t tam = 0;
    int i = 0;
    unsigned char u;
    while (s[i] != 0) {
        u = s[i];
        if (u < 0x80) tam++;
        else if (u >= 0xC0 && u <= 0xF7) tam++;
        i++;
    }
    return tam;
}

//7.1.1 (UTF-8)
int main() {
    char s[20]="vou";
    printf("Tem %s palavras.", strlen_u8(s));
}

char strlen_u8(const char) {
    int i = 0;
    unsigned char u;
    while (s[i] != 0) {
        u = s[i];
        if (u>=0x61 && u<=0x7A) s[i]= u - 0x20;
        i++;
    }
    return s;
}

//Ex 7.2.1
#define MAX 50

int comprime(char cadeia[50], int i);

int main() {
    char cadeia[MAX], cad2[MAX];
    int i = 0, n, n2 = 0, m = 0, v = 0, count = 1, final;
    printf("Introduza a cadeia de números: \n");
    while ((n = getchar()) != '\n' && i != MAX) {
        n = n - '0';
        cadeia[i] = n;
        i++;
    }
    comprime(cadeia, i);
    return 0;
}

int comprime(char cadeia[50], int i) {
    int n, v = -1, count = 1, final, l;
    for (n = 0; n < i; n++) {
        if (cadeia[n] == cadeia[n + 1]) {
            count++;
            v = 1;
        } else if (cadeia[n] != cadeia[n + 1]) {
            final = count;
            count = 1;
            v = 0;
        }
        if (v == 0 && final > 4) {
            printf("c%d%df", cadeia[n], final);
        } else if (v == 0 && final <= 4) {
            for (l = 0; l < final; l++) {
                printf("%d", cadeia[n]);
            }
        }
    }
    return i;
}

//7.2.2
#define MAX 50

int codifica(char cadeia[MAX], int tam, int num);

int main() {
    char cadeia[MAX];
    int n, tam = 0, num;
    printf("Introduza a cadeia: ");
    while ((n = getchar()) != '\n' && tam < MAX) {
        cadeia[tam] = n;
        tam++;
    }
    printf("Introduza um número: ");
    scanf(" %d", &num);
    codifica(cadeia, tam, num);
    return 0;
}

int codifica(char cadeia[MAX], int tam, int num) {
    int n;
    char copy_cad[MAX], copy2[MAX];
    printf("Resultado intermédio: ");
    for (n = 0; n < tam; n++) {
        copy_cad[n] = cadeia[n] + (num % tam);
        if (copy_cad[n] > 0x7E) {
            copy_cad[n] = copy_cad[n] - copy_cad[n] + 0x21;
        }
    }
    printf("%s\n", copy_cad);
    printf("Resultado Final: ");
    for (n = 0; n < tam; n++) {
        if (n < num) copy2[n] = copy_cad[tam - num + n];
        else copy2[n] = copy_cad[n - num];
    }
    for (n = 0; n < tam; n++) copy_cad[n] = copy2[n];
    printf("%s\n", copy_cad);
    return tam;
}

//7.2.3
#define MAX 50

const char *get_cad(char cadeia[MAX], int tam, int *pi);

int find_wally(char cadeia[MAX], int tam);

int main() {
    char cadeia[MAX];
    int tam = 0, pos_wally = 0, *pi;
    pi = &tam;
    get_cad(cadeia, tam, pi);
    pos_wally = find_wally(cadeia, tam);
    if (pos_wally == -1) printf("Palavra não encontrada.");
    else printf("Esta cadeia tem a palavra Wally na posição %d.", pos_wally);
    return 0;
}

const char *get_cad(char cadeia[MAX], int tam, int *pi) {
    int n;
    printf("Introduza a cadeia: ");
    while ((n = getchar()) != '\n' && tam < MAX) {
        cadeia[tam] = n;
        tam++;
    }
    *pi = tam;
    return cadeia;
}

int find_wally(char cadeia[MAX], int tam) {
    char cad_wally[6] = "Wally";
    int cont = 0, pos = 0;
    for (int i = 0; i < tam; i++) {
        if (cadeia[i] == cad_wally[cont]) {
            cont++;
            if (cont == 5) return pos - 4;
        } else if (cadeia[i] != cad_wally[cont]) cont = 0;
        if (pos == tam - 1 && cont != 5) return -1;
        pos++;
    }
}
*/
//7.2.3
# include <string.h>

#define MAX 1000
#define MAXPASS 20

const char *get_cad(char cadeia[MAX], int tam, int *pi);

int find_pass(char cadeia[MAX], char cad_pass[MAXPASS], int tam, int tam_pass);

int count_cad(char cadeia[MAX], int tam);

const char *codifica(char cadeia[MAX], char cad_pass[MAXPASS], char cadeia_mod[MAX], int tam, int num, int tam_pass);

int main() {
    char cadeia[MAX], cad_pass[MAXPASS], cadeia_mod[MAX];
    int tam = 0, pos_pass = 0, *pi, tam_pass = 0, n, n_palavras, num = 1;
    pi = &tam;
    printf("Introduza a palavra-chave: ");
    while ((n = getchar()) != '\n' && tam_pass < MAXPASS) {
        cad_pass[tam_pass] = n;
        tam_pass++;
    }
    get_cad(cadeia, tam, pi);
    pos_pass = find_pass(cadeia, cad_pass, tam, tam_pass);
    n_palavras = count_cad(cadeia, tam);
    codifica(cadeia, cad_pass, cadeia_mod, tam, num, tam_pass);
    printf("Esta cadeia tem a palavra %s %d vez/es.\n", cad_pass, pos_pass);
    printf("A cadeia tem %d palavras.\n", n_palavras);
    printf("Cadeia com palavra chave codificada: %s", cadeia_mod);
    return 0;
}

const char *get_cad(char cadeia[MAX], int tam, int *pi) {
    int n;
    printf("Introduza a cadeia: ");
    while ((n = getchar()) != '\n' && tam < MAX) {
        cadeia[tam] = n;
        tam++;
    }
    *pi = tam;
    return cadeia;
}

int find_pass(char cadeia[MAX], char cad_pass[MAXPASS], int tam, int tam_pass) {
    int cont = 0, pos = 0;
    for (int i = 0; i < tam; i++) {
        if (cadeia[i] == cad_pass[pos]) {
            pos++;
            if (pos == tam_pass) cont++;
        } else if (cadeia[i] != cad_pass[pos]) pos = 0;
    }
    return cont;
}

int count_cad(char cadeia[MAX], int tam) {
    int cont = 0;
    for (int i = 0; i < tam; i++) {
        if (cadeia[i] == ' ' || cadeia[i] == '.' || cadeia[i] == EOF) cont++;
    }
    return cont;
}

const char *codifica(char cadeia[MAX], char cad_pass[MAXPASS], char cadeia_mod[MAX], int tam, int num, int tam_pass) {
    int n, cont = 0, pos=0;
    char copy_cad[MAXPASS], copy2[MAXPASS];
    for (n = 0; n < tam; n++) {
        copy_cad[n] = cad_pass[n] + (num % tam);
        if (copy_cad[n] > 0x7E) {
            copy_cad[n] = copy_cad[n] - copy_cad[n] + 0x21;
        }
    }
    for (n = 0; n < tam; n++) {
        if (n < num) copy2[n] = copy_cad[tam - num + n];
        else copy2[n] = copy_cad[n - num];
    }
    for (n = 0; n < tam; n++) copy_cad[n] = copy2[n];
    for (int i = 0; i < tam; i++) {
        if (cadeia[i] == cad_pass[cont]) {
            pos = i;
            cont++;
            if (cont == tam_pass)
                for (int i=pos; i<tam_pass; i++)
                    cadeia_mod[i]=copy_cad[i];
        } else {
            cont = 0;
            cadeia_mod[i] = cadeia[i];
            pos = 0;
        }
    }
    return cadeia_mod;
}
