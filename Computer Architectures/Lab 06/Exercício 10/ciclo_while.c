int (int a, int b){
  int cont=0;
  int first=(b-a);
  int second=(b+a);
  while(cont<=b-1){
   first*=(b-a);
   cont++;
  }
  cont=0;
  while(cont<a-1){ 
    second*=(b+a);
    cont++;
  }
  c=first+second;
  return c;
}
    