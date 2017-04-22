#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "funcionesmtz.h"
#include <pthread.h>

void* hilosum(void*arg);
void* hilores(void*arg);


int main(void) {
//arreglo de matrices
  int m1 [2][10][10]={{{0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2}}
                   ,
                   {{0,1,2,3,3,2,1,0,1,2},
                    {0,1,2,3,3,2,1,0,1,2},
                    {0,1,2,3,3,2,1,0,1,2},
                    {0,1,2,3,3,2,1,0,1,2},
                    {0,1,2,3,3,2,1,0,1,2},
                    {0,1,2,3,3,2,1,0,1,2},
                    {0,1,2,3,3,2,1,0,1,2},
                    {0,1,2,3,3,2,1,0,1,2},
                    {0,1,2,3,3,2,1,0,1,2},
                    {0,1,2,3,3,2,1,0,1,2}}};


  pthread_t id_hilo1,id_hilo2;
  //suma
  pthread_create(&id_hilo1,NULL,hilosum,(void*)m1);
  //resta
  pthread_create(&id_hilo2,NULL,hilores,(void*)m1);

  pthread_join(id_hilo2,NULL);

  return 0;
}

void* hilosum(void *arg){
  int (*men)[10][10]=arg;
  int m1[10][10],m2[10][10];

  /*LLenamos las nuevas matrices (solamente por comodidad
  de uso de funciones ya implementadas)*/
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m1[i][j]=men[0][i][j];
      }
    }
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m2[i][j]=men[1][i][j];
      }
    }
    /*suma de matrices*/
    int m3 [10][10];
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m3[i][j]=m1[i][j]+m2[i][j];
      }
    }
    /*impresion de suma de matrices*/
    printf("\nSuma de matrices\n");
    CreaArchivo(m3,"/home/andres/Documents/s.o/O.S/p5/msuma.txt");
    LeeArchivo("/home/andres/Documents/s.o/O.S/p5/msuma.txt");
    return NULL;
}

void* hilores(void *arg){
  int (*men)[10][10]=arg;
  int m1[10][10],m2[10][10];

  /*LLenamos las nuevas matrices (solamente por comodidad
  de uso de funciones ya implementadas)*/
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m1[i][j]=men[0][i][j];
      }
    }
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m2[i][j]=men[1][i][j];
      }
    }
    /*suma de matrices*/
    int m3 [10][10];
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m3[i][j]=m1[i][j]-m2[i][j];
      }
    }
    /*impresion de suma de matrices*/
    printf("\nResta de matrices\n");
    CreaArchivo(m3,"/home/andres/Documents/s.o/O.S/p5/mresta.txt");
    LeeArchivo("/home/andres/Documents/s.o/O.S/p5/mresta.txt");
    return NULL;
}
