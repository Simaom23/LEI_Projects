#include <stdio.h>
#include "soma.h"
#include "soma_octal.h"

int main(){
  int a,b,c;
  printf("Enter the first number: ");
  scanf("%d",&a);
  printf("Enter the second number: ");
  scanf("%d",&b);
  c=soma(a,b);
  printf("The sum in decimal of %d with %d is %d \n",a,b,c);
  soma_octal(a,b,c);
  c=ciclo_for(a,b);
  printf("%d\n",c);
}
