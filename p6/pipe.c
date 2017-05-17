#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define VALOR 1

int main(void){
  int desc_arch[2];
  char buffer[100];
  int id_proc;
  if(pipe(desc_arch)!=0)
    exit(1);
  if((id_proc=fork())==0){
    while(VALOR){
      read(desc_arch[0],buffer,sizeof(buffer));
      printf("Se recibio: %s\n",buffer);
    }
  }
  if((id_proc=fork())==0){
    while(VALOR){
      gets(buffer);
      write(desc_arch[1],strcat(buffer," desde hijo 1"),strlen(buffer)+14);
    }
  }
  if((id_proc=fork())==0){
    while(VALOR){
      gets(buffer);
      write(desc_arch[1],strcat(buffer," desde hijo 2"),strlen(buffer)+14);
    }
  }
}
