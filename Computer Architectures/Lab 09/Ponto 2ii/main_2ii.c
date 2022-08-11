#include<stdio.h>

int oddnumber(int *ptr,int *ptr2,int *ptr3, int n);

int main ( )
{
	int tab[]={1,2,3,4,5,6,7,8,9,10};
	int tabodd[10];
	int tabeven[10];
	int n=10;
	int i,x;
	
	printf(" O Array original: ");
	for(i=0;i<9;i++){
		printf("%d , ",tab[i]);
	}
  
	printf("%d \t ",tab[i]);
	x=oddnumber(tab, tabodd,tabeven,n);
	printf("possui %d números ímpares\n",x);

	printf(" Lista de números ímpares: ");
	for(i=0;i<x -1;i++){
		printf("%d , ",tabodd[i]);
	}
	printf("%d \n ",tabodd[i]);
 
	printf(" Lista de números pares: ");
	/*
	
	Desenvolver o código que falta aqui
	
	*/
	
}