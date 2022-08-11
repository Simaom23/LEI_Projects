#include <stdlib.h>
#include <stdio.h>

int Polycalc(int *tab);

int main(){
	int *tab;
	int resultado,val,i;
	

	tab = (int *) malloc(6*sizeof(int));

	printf("Introduza seis numeros: ");
	for(i=0;i<6;i++){
		scanf("%d",&tab[i]);
	}

	resultado = Polycalc(tab);
	val=tab[0]+tab[1]/2+tab[2]/4+tab[3]/8+tab[4]/16+tab[5]/32;
	
	printf("Resultado esperado: %d\n", val);
	printf("Resultado calculado com funcao Polycalc: %d\n", resultado);
	

	return 0;
}