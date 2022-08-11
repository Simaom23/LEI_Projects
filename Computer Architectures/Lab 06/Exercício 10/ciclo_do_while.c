int (int a, int b){
  int cont=0;
  int first=(b-a);
  int second=(b+a);
  do{
    first*=(b-a);
    cont++;
  }while(cont<=b-1);
  cont=0;
  do{
    second*=(b+a);
    cont++;
  }while(cont<a-1); 
  c=first+second;
  return c;
}