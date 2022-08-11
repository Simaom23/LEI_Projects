#include<stdio.h>

void convertMaisculas(char *ptr);

int main ( )
{
	char str[50];

	printf("Introduza uma string: ");
	fgets (str, sizeof(str), stdin);
	
	printf("String original: %s\n", str);
	
	convertMaisculas(str);
	
	printf("String final: %s\n", str);
}