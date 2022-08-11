int (int a, int b){
  int first=(b-a);
  int second=(b+a);
  for (int i=0; i<b-1; i++)
    first*=(b-a);
  for (int i=0; i<a-1; i++)
    second*=(b+a)
  c=first+second;
  return c;
}