#include <stdlib.h>
#include <stdio.h>

#define CHAVE 'Z'

void codificastring(char *frase, char chave);

int main(){
	char frase[20];
	char chave;

	printf("Introduza uma frase: ");
	fgets (frase, sizeof(frase), stdin);

	printf("Frase Original: %s\n",frase);
	codificastring(frase,CHAVE);

	printf("Frase Encriptada: %s\n",frase);
	codificastring(frase,CHAVE);
	
	printf("Frase Desencriptada: %s\n",frase);

	return 0;
}