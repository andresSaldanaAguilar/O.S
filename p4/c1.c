#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
  int idproc;

  if((idproc=fork())==0){
    printf("Soy el proceso hijo 1.\n");
    exit(0);
  }

  if((idproc=fork())==0){
    printf("Soy el proceso hijo 2.\n");
    exit(0);
  }

  if((idproc=fork())==0){
    printf("Soy el proceso hijo 3.\n");
    exit(0);
  }
  else{
    printf("Soy el proceso padre.\n");
    exit(0);
  }

}
