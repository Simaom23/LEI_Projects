#include <stdio.h>

int conta_char(unsigned char *str, unsigned char car);

int main ()
{
	unsigned char str[50], car;
	int num;
	
	printf ("Introduza a String:\n");
	fgets(str, 50, stdin); // Lê a string
	printf ("Indique o caracter a procurar:\n");
	scanf ("%c", &car);
	num = conta_char(str, car);
	printf ("O caracter '%c' aparece %d vezes na String!\n",car,num);
	return 0;
}
