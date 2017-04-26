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

float determinante(float [][25], float);
void cofactor(float [][25], float);
void Transpuestainv(float [][25], float [][25], float);
void* hilosum(void*arg);
void* hilores(void*arg);
void* hilomult(void*arg);
void* hilotransp(void *arg);
void* hiloinv(void *arg);
void* hiloimprime(void *arg);

int main(void) {
  clock_t start_t, end_t;
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

//esta matriz es especial para la inversion porque no cualquier matriz puede tener inversa
float a [25][25]={{0,2,0,1,3,3,0,3,2,0},
                  {1,0,3,2,3,0,1,5,4,1},
                  {0,1,0,2,3,3,0,3,2,0},
                  {1,0,0,2,3,3,0,3,2,2},
                  {1,2,3,4,3,0,1,5,4,1},
                  {1,0,2,0,3,3,0,3,5,0},
                  {1,1,3,2,3,0,1,3,0,2},
                  {3,0,5,2,3,3,0,3,2,2},
                  {0,2,2,3,3,6,1,0,5,2},
                  {0,1,2,2,3,3,0,3,2,2}};

  start_t = clock();

  pthread_t id_hilo1,id_hilo2,id_hilo3,id_hilo4,id_hilo5,id_hilo6;
  //suma
  pthread_create(&id_hilo1,NULL,hilosum,(void*)m1);
  //resta
  pthread_create(&id_hilo2,NULL,hilores,(void*)m1);
  //mult
  pthread_create(&id_hilo3,NULL,hilomult,(void*)m1);
  //transp
  pthread_create(&id_hilo4,NULL,hilotransp,(void*)m1);
  //inversa
  pthread_create(&id_hilo5,NULL,hiloinv,(void*)a);
  //Imprime
  pthread_create(&id_hilo6,NULL,hiloimprime,NULL);
  //espera por hilos a acabar
  pthread_join(id_hilo6,NULL);

  end_t = clock();
  double t = (float)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("\nTiempo tomado por la CPU (hilos): %f\n", t);

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
    CreaArchivo(m3,"/home/andres/Documents/s.o/O.S/p5/msuma.txt");
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
    /*resta de matrices*/
    int m3 [10][10];
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m3[i][j]=m1[i][j]-m2[i][j];
      }
    }
    CreaArchivo(m3,"/home/andres/Documents/s.o/O.S/p5/mresta.txt");
    return NULL;
}

void* hilomult(void *arg){
  int (*men)[10][10]=arg;
  int m1[10][10],m2[10][10];

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
    int m3 [10][10];
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m3[i][j]=m1[i][j]*m2[i][j];
      }
    }
    CreaArchivo(m3,"/home/andres/Documents/s.o/O.S/p5/mmult.txt");
    return NULL;
}

void* hilotransp(void *arg){
  int (*men)[10][10]=arg;
  int m1[10][10],m2[10][10];

  for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m1[i][j]=men[0][j][i];
      }
    }
    CreaArchivo(m1,"/home/andres/Documents/s.o/O.S/p5/mt1.txt");
    return NULL;
}

/*Calculando el determinante de la matriz , metodos para inversion de matriz*/
float determinante(float a[25][25], float k){
  float s = 1, det = 0, b[25][25];
  int i, j, m, n, c;
  if (k == 1)
    {
     return (a[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < k; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < k; i++)
          {
            for (j = 0 ;j < k; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[m][n] = a[i][j];
                   if (n < (k - 2))
                    n++;
                   else
                    {
                     n = 0;
                     m++;
                     }
                   }
               }
             }
          det = det + s * (a[0][c] * determinante(b, k - 1));
          s = -1 * s;
          }
    }
    return (det);
}

/*Encontrando cofactor*/
void cofactor(float num[25][25], float f){
 float b[25][25], fac[25][25];
 int p, q, m, n, i, j;
 for (q = 0;q < f; q++)
 {
   for (p = 0;p < f; p++)
    {
     m = 0;
     n = 0;
     for (i = 0;i < f; i++)
     {
       for (j = 0;j < f; j++)
        {
          if (i != q && j != p)
          {
            b[m][n] = num[i][j];
            if (n < (f - 2))
             n++;
            else
             {
               n = 0;
               m++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinante(b, f - 1);
    }
  }
  Transpuestainv(num, fac, f);
}

/*Encontrando la Transpuestainv de la matriz*/
void Transpuestainv(float num[25][25], float fac[25][25], float r){
  int i, j;
  float b[25][25], inversa[25][25], d;
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         b[i][j] = fac[j][i];
        }
    }
  d = determinante(num, r);
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
        inversa[i][j] = b[i][j] / d;
        }
    }
    CreaArchivoInv(inversa,"/home/andres/Documents/s.o/O.S/p4/matriz/msinv.txt");
}

void* hiloinv(void *arg){
  float (*men)[10]=arg;
  float k=10, d;

  printf("\nInversa de matrices:\n");
  d = determinante(men, k);
  if (d == 0)
   printf("\nLa inversa de la matriz no es posible.\n");
  else
   cofactor(men, k);
   return NULL;
}

void* hiloimprime(void *arg){
  printf("\nSuma de matrices:\n");
  LeeArchivo("/home/andres/Documents/s.o/O.S/p4/matriz/msuma.txt");
  printf("\nResta de matrices:\n");
  LeeArchivo("/home/andres/Documents/s.o/O.S/p4/matriz/mresta.txt");
  printf("\nMultiplicacion de matrices:\n");
  LeeArchivo("/home/andres/Documents/s.o/O.S/p4/matriz/mltp.txt");
  printf("\nTranspuesta de matrices:\n");
  LeeArchivo("/home/andres/Documents/s.o/O.S/p4/matriz/mtrp.txt");
  printf("\nInversa de matrices:\n");
  LeeArchivoInv("/home/andres/Documents/s.o/O.S/p4/matriz/msinv.txt");
  return NULL;
}
