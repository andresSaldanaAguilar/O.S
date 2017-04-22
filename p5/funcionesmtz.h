#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void CreaArchivo(int m1[10][10],char *fn){
  int fd;
  char int2Str[1];
  char aux[10];
  char c;

  if ((fd = creat(fn, S_IRUSR | S_IWUSR)) < 0){
    perror("creat() error");
  }
  else {
    for (int i = 0;i<10;i++) {
        *aux='0';
        *int2Str='0';
        for(int j=0;j<10;j++){
          c=m1[i][j]+'0';
          sprintf(int2Str,"%c",c);
          write(fd,int2Str,sizeof(int2Str));
        }
    }
        close(fd);
  }
}

void LeeArchivo(char *cadena){
  int fd;
  char c;

  fd = open(cadena,O_RDONLY);
  if(fd!=-1)
    {
      //Leemos el archivo
      //El archivo se lee caracter por caracter
      int i=0;
      while(read(fd,&c,sizeof(c)!=0)){
        if(i==90||i==80||i==70||i==60||i==50||i==40||i==30||i==20||i==10||i==100){
          printf("\n");
        }
        printf("%c ",c);
        i++;
    }
      //Cerramos archivo
      close(fd);
    }
  else{
    printf("\nEl archivo no existe.\n");
  }
}

void CreaArchivoInv(float m1[25][25],char *fn){
  int fd;
  char int2Str[4];
  char aux[50];
  float c;

  if ((fd = creat(fn, S_IRUSR | S_IWUSR)) < 0){
    perror("creat() error");
  }
  else {
    for (int i = 0;i<10;i++) {
        *aux='0';
        *int2Str='0';
        for(int j=0;j<10;j++){
          c=m1[i][j];
          sprintf(int2Str,"%0.1f",c);
          write(fd,int2Str,sizeof(int2Str));
        }
    }
        close(fd);
  }
}

void LeeArchivoInv(char *cadena){
  int fd;
  char c;

  fd = open(cadena,O_RDONLY);
  if(fd!=-1)
    {
      //Leemos el archivo
      //El archivo se lee caracter por caracter
      int i=0;
      while(read(fd,&c,sizeof(c)!=0)){
        if(i==400||i==360||i==320||i==280||i==240||i==200||i==160||i==120||i==80||i==40){
          printf("\n");
        }
        printf("%c ",c);
        i++;
    }
      //Cerramos archivo
      close(fd);
    }
  else{
    printf("\nEl archivo no existe.\n");
  }
}
