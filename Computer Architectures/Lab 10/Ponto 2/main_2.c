#include <stdio.h>

void manipula_array(int *ptr, int dim);

int main()
{
	int i;	
	int dim=10;
	int array[]={1,2,3,4,5,6,7,8,9,10}; 

	printf("Array original: ");
	for(i=0;i<9;i++){
		printf("%d -> ",array[i]);
	}
	printf("%d \n",array[9]);
	
	manipula_array(array,dim);
	
	printf("Array manipulado e invertido: ");
	for(i=0;i<9;i++){
		printf("%d -> ",array[i]);
	}
	printf("%d\n",array[9]);
		
return 0;
}
