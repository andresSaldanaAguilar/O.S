#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    int idproc;
    idproc=fork();
    if(idproc==0){
      printf("Soy el proceso hijo.\n");
    }
    else{
      printf("Soy el proceso padre.\n");
    }
    printf("Mensaje en ambos.\n");
    exit(0);
}
