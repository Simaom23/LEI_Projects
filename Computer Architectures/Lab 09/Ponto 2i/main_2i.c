#include<stdio.h>

int oddnumber(int *ptr, int n);

int main ( )
{
	int tab[]={1,2,3,4,5,6,7,8,9,10};
	int n=10;
	int i;
	
	printf(" O Array original: ");
	for(i=0;i<n;i++){
		printf("%d , ",tab[i]);
	}
	printf("\n\n");

  printf("Esta tabela possui %d números ímpares\n",oddnumber(tab, n));
		
}