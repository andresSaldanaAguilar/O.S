#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char const *argv[]) {
  int fd;
  char c;
  char * cadena = NULL;
  int tamanio = 50;


  //Leemos la direccion del archivo a abrir
  cadena = (char *)calloc(tamanio, sizeof(char));
  printf("%s", "Escriba la direccion del directorio:");
  scanf("%s", cadena);

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
  return 0;
}
