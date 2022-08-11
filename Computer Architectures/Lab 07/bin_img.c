void bin_img(unsigned char *ptr, int w, int h, unsigned char limiar){
  int i;
  for(i=0; i<w*h; i++){
    if(ptr[i]<limiar)  ptr[i]=0;
    else  ptr[i]=255;
  };
}