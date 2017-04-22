#include <stdio.h>
#include <pthread.h>
void*hilo(void*arg);
void*hilo1(void*arg);

int main(void){
  pthread_t id_hilo,id_hilo1;
  printf("hola cara de cola\n");
  pthread_create(&id_hilo1,NULL,(void*)hilo1,NULL);
  pthread_create(&id_hilo,NULL,(void*)hilo,NULL);
  //thread join, espera a que el hilo especificado termine su ejecucion para proseguir
  pthread_join(id_hilo1,NULL);
  return 0;
}

void *hilo(void *arg){
  printf("Hola mundo desde hilo 1\n");
  int x=3,y=4;
  printf("%i\n",x+y);
  return NULL;
}

void *hilo1(void *arg){
  printf("Hola mundo desde hilo 2\n");
  return NULL;
}
