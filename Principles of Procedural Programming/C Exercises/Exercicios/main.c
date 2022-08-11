#include <stdio.h>
/*
//EX  1.1.1
int main(){
    int idade=18, peso=78;
    printf("Chamo me Simão, tenho %d anos e peso %d KG.", idade, peso);
}

//EX  1.1.2
int main() {
    int peso, idade;
    printf("Qual é a sua idade?\t");
    scanf("%d", &idade);
    printf("Qual é o seu peso?\t");
    scanf("%d", &peso);
    printf("Tenho %d anos e peso %d Kg.", idade, peso);
    return 0;
}


//EX 1.2.1
int main() {
    float preço, pagamento;
    char nota5 = 5, nota10 = 10, nota20 = 20, nota50 = 50, moeda1 = 1, moeda2 = 2;
    float cent1 = 0.01, cent2 = 0.02, cent5 = 0.05, cent10 = 0.10, cent20 = 0.20, cent50 = 0.50;
    printf("Qual foi o preço da compra?\t");
    scanf("%d", &preço;
    printf("Qual foi o pagamento recebido\t");
    scanf("%d", &pagamento);
    float troco = pagamento - preço;
    return 0;
}

//Ex 2.1.1
int main() {
    int numero;
    printf("Introduza um número par:\t");
    scanf("%d", &numero);
    if (numero % 2 == 0) printf("O número %d é par.", numero);
    else printf("O número %d é ímpar.", numero);
    return 0;
}

//Ex 2.1.2
int main() {
    int numero1, numero2, numero3, max = 0;
    printf("Introduza 3 números, separados por espaços: ");
    scanf("%d %d %d", &numero1, &numero2, &numero3);
    if (numero1 > max)max = numero1;
    if (numero2 > max)max = numero2;
    if (numero3 > max)max = numero3;
    printf("O número maior é %d.", max);
    return 0;
}

//Ex 2.1.3
int main() {
    int numero1, numero2;
    printf("Introduza 2 números, separados por espaços: ");
    scanf("%d %d", &numero1, &numero2);
    if (numero1 % 2 == 0 && numero2 % 2 == 0)
        printf("Ambos os números são pares e a sua soma é %d.", numero1 + numero2);
    else if (numero1 % 2 != 0 && numero2 % 2 != 0)
        printf("Ambos os números são ímpares e o seu produto é %d.", numero1 * numero2);
    else {
        if (numero1 % 2 != 0) printf("Existe um número par e um número ímpar e o número ímpar é %d.", numero1);
        else printf("Existe um número par e um número ímpar e o número ímpar é %d.", numero2);
    }
    return 0;
}

//Ex 2.2.1
int main() {
    int idade;
    printf("Introduza a sua idade: ");
    scanf("%d", &idade);
    if (idade <= 12) printf("É isento de pagamento.");
    else if (idade >= 13 && idade <= 24) printf("O seu bilhete é o bilhete radical.");
    else if (idade >= 25 && idade <= 36) printf("O seu bilhete é o bilhete light.");
    else if (idade >= 37 && idade <= 48) printf("O seu bilhete é o bilhete normal.");
    else if (idade >= 49 && idade <= 60) printf("O seu bilhete é o bilhete light.");
    else printf("É isento de pagamento.");
    return 0;
}

//Ex 2.2.2
int main() {
    int horas, minutos;
    char periodo_manha[] = "AM", periodo_tarde[] = "PM", flag = 0;
    int first_format[12], second_format[12];
    for (char i = 0; i < 12; i++) first_format[i] = i + 13;
    for (char i = 0; i < 12; i++) second_format[i] = i + 1;
    printf("Introduza as horas (no formato hora:minutos): ");
    scanf("%d:%d", &horas, &minutos);
    for (char i = 0; i < 12; i++) {
        if (first_format[i] == horas) {
            horas = second_format[i];
            flag = 1;
            printf("A conversão é %02d:%02d %s", horas, minutos, periodo_tarde);
        }
    }
    if (flag == 0) printf("A conversão é %02d:%02d %s", horas, minutos, periodo_manha);
    return 0;
}

//Ex 2.2.3
int main() {
    int nota;
    printf("Introduza a sua nota: ");
    scanf("%d", &nota);
    if (nota >=0 && nota <= 9) printf("A sua nota é Insuficiente.");
    else if (nota >= 10 && nota <= 13) printf("A sua nota é um Suficiente.");
    else if (nota >= 14 && nota <= 16) printf("A sua nota é um Bom.");
    else if (nota >= 17 && nota <= 20) printf("A sua nota é um Excelente.");
    else printf("Introduza uma classificação possível!");
    return 0;
}

//Ex 2.2.4
int main(){
    int dia,mes;
    printf("Insira uma data no formato dia/mes: ");
    scanf("%d/%d", &dia,&mes);
}

//Ex 2.2.5
#include <stdlib.h>
int main(){
    int flag=1,dado1,dado2;
    printf("Introduza o número 0 para lançar os dois dados: ");
    while(1){
        dado1=rand()%6+1;
        dado2=rand()%6+1;
        scanf("%d",flag);
    }
    if(dado1>dado2){
        if(dado1-dado2<4) printf("A diferença é inferior a 4.");
        if(dado1-dado2<2) printf("A diferença é inferior a 2.");
        else if(dado1-dado2>3) printf("A diferença é superior a 3.");
    }
    if(dado2>dado1){
        if(dado2-dado1<4) printf("A diferença é inferior a 4.");
        if(dado2-dado1<2) printf("A diferença é inferior a 2.");
        else if(dado2-dado1>3) printf("A diferença é superior a 3.");
    }
    return 0;
}

//Ex 2.2.6
int main(){
    int mes;
    printf("Introduza o número do mês: ");
    scanf("%d", &mes);
    if (mes == 1) printf ("Janeiro.");
    else if (mes == 2) printf("Fevereiro.");
    else if (mes == 3) printf("Março.");
    else if (mes== 4) printf("Abril.");
    else if (mes == 5) printf("Maio.");
    else if (mes == 6) printf("Junho.");
    else if (mes== 7) printf("Julho.");
    else if (mes == 8) printf("Agosto.");
    else if (mes == 9) printf("Setembro.");
    else if (mes== 10) printf("Outubro.");
    else if (mes ==11) printf("Novembro.");
    else if (mes == 12) printf("Dezembro.");
    else printf("Introduza um número de um mês existente!");
    return 0;
}

//Ex 2.2.7
int main(){

}

//Ex 2.3.1
int main() {
    int cartao_original, cartao_criado, soma_digito = 0;
    printf("Introduza um número de cartão original para criar um novo: ");
    scanf("%d", &cartao_original);
    cartao_criado = cartao_original;
    while (cartao_original > 0) {
        soma_digito += cartao_original % 10;
        cartao_original /= 10;
    }
    if (soma_digito % 2 == 0) cartao_criado = cartao_criado * 10;
    else cartao_criado = cartao_criado * 10 + 1;
    printf("O novo número de cartão é: %d", cartao_criado);
    return 0;
}
//2.3.2
int main(){
    int dia,mes,ano;
    char mes_string[]={"Janeiro","Fevereiro","Março","Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro",
                       "Novembro","Dezembro"};
    printf("Introduza a sua data no formato dia/mes/ano: ");
    scanf("%d/%d/%d",&dia,&mes,&ano);
}

//3.1.1
int calcular_soma(int n){
   if(n>=2) return (n+calcular_soma(n-1));
   else  return (1);
}
int main(){
   int n;
   printf("Introduza o número: ");
   scanf("%d",&n);
   printf("%d",calcular_soma(n));
}

//3.1.2
int main() {
    int n, soma = 1,cont=1;
    printf("Introduza o número onde quer que pare a soma: ");
    scanf("%d", &n);
    while (soma < n) {
        cont++;
        soma += cont;
    }
    printf("A soma dá %d e o último número adicionado foi %d.", soma, cont);
    return 0;
}

//3.1.3
int main() {
    int n, min, cont_N, cont = 1;
    printf("Qual o tamanho do conjunto N (números): ");
    scanf("%d", &cont_N);
    printf("Número: ");
    scanf("%d", &n);
    min = n;
    while (cont <= cont_N - 1) {
        printf("Número: ");
        scanf("%d", &n);
        cont++;
        if (n < min) min = n;
    }
    printf("O número menor do conjunto N é %d.", min);
    return 0;
}

//Ex 3.1.4
int main() {
    int n, cont = 0;
    printf("Introduza um número entre 1 e 100: ");
    scanf("%d",&n);
    for (int i = 0; i <= 100; i++) {
        cont++;
        if (n >= i) {
            if (n % i == 0 && cont <= 4) printf("%d", i);
        } else if (i % n == 0 && cont <= 4) printf("%d", i);
    }
    return 0;
}

//Ex 3.1.5
int string_print(char cont) {
    char cont_asteriscos = 1;
    while (cont_asteriscos <= cont) {
        printf("*");
        cont_asteriscos++;
    }
}
int main() {
    char n, cont = 1;
    printf("Quantas vezes correr o padrão? ");
    scanf("%d", &n);
    while (cont <= n) {
        string_print(cont);
        printf("\n");
        cont++;
    }
}
//Ex 3.2.3
int main() {
    int n, m, min;
    printf("Introduza um número n e um número m separado por espaços: ");
    scanf("%d %d", &n, &m);
    if (n > m) min = m;
    else min = n;
    for (int i = 2; i <= min; i++)
        if (n % i == 0 && m % i == 0) {
            printf("O mínimo divisor comum é: %d", i);
            break;
        }
    return 0;
}
//Ex 3.2.5
int main(){
    int n,soma_digito;
    printf("Introduza um número: ");
    scanf("%d", &n);
    while (n > 0) {
        soma_digito += n % 10;
        n /= 10;
    }
    printf("A soma dos digítos o número introduzido é: %d", soma_digito);
    return 0;
}
*/
//Ex 4.1.1
int fatorial(n){
    if(n==1) return 1;
    else return(n*fatorial(n-1));

}
int main(){
    int n;
    printf("Calcular fatorial de: ");
    scanf("%d", &n);
    fatorial(n);
    return 0;
}
