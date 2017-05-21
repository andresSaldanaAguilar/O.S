#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include "funcionesmtz.h"
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>

#define FILEKEY "/bin/cat"
#define MAXBUF 300


float determinante(float [][25], float);
void cofactor(float [][25], float);
void Transpuestainv(float [][25], float [][25], float);

int main (void) {

  //matriz 1
  int m1 [10][10]={
                  {0,2,0,1,3,3,0,3,2,0},
                  {1,0,3,2,3,0,1,5,4,1},
                  {0,1,0,2,3,3,0,3,2,0},
                  {1,0,0,2,3,3,0,3,2,2},
                  {1,2,3,4,3,0,1,5,4,1},
                  {1,0,2,0,3,3,0,3,5,0},
                  {1,1,3,2,3,0,1,3,0,2},
                  {3,0,5,2,3,3,0,3,2,2},
                  {0,2,2,3,3,6,1,0,5,2},
                  {0,1,2,2,3,3,0,3,2,2}};
  //matriz 2
  int m2 [10][10]={{1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},};

   /* Llaves de memoria compartida*/
   int KEY[4]={1301,1302,1303,1304};
   int key[4],zona_id[4];
   int *buffer[4];

   /*creamos los 4 buffers necesarios*/
   for(int i=0;i<4;i++){
   key[i] = ftok(FILEKEY, KEY[i]);
   if (key[i] == -1) {
      fprintf (stderr, "Error en la llave %i.\n",i);
      return -1;
   }

   /*Creamos la memoria compartida*/
   zona_id[i] = shmget (key[i], sizeof(int)*MAXBUF, 0777 | IPC_CREAT);
   if (zona_id[i] == -1) {
      fprintf (stderr, "Error en la zona_id. %i\n",i);
      return -1;
   }

   printf ("Zona ID de la memoria compartida: %i --> %i\n", zona_id[i],i);

   /*declaramos zona a compartir*/
   buffer[i] = shmat (zona_id[i], (char *)0, 0);
   if (buffer[i] == NULL) {
      fprintf (stderr, "Error reservando memoria.\n");
      return -1;
   }
   printf ("Apuntador a buffer: %p --> %i\n", buffer[i],i);
   }


  /*empezamos con el manejo de los procesos*/

  /*procedemos a llenar el buffer con las matrices que mandara el padre a hijo*/
  int contador_padre=0;
  for(int i=0;i<10;i++){
    for (int j = 0; j < 10; j++){
       buffer[0][contador_padre] = m1[i][j];
       contador_padre++;
    }
  }
  for(int k=0;k<10;k++){
    for (int l = 0; l < 10; l++){
       buffer[0][contador_padre] = m2[k][l];
       contador_padre++;
    }
  }

  /*creacion de porceso hijo*/
  int idproc;
  if((idproc=fork())==0){
    printf("Soy el hijo\n");
    int m1n1 [10][10], m2n1 [10][10], mmult [10][10];
    int aux=0;
    /*llenamos las matrices y efectuamos suma*/
    for(int i=0;i<10;i++){
      for (int j = 0; j < 10; j++){
           m1n1[i][j]=buffer[0][aux];
           aux++;
      }
    }
    for(int l=0;l<10;l++){
      for (int m = 0; m < 10; m++){
           m2n1[l][m]=buffer[0][aux];
           aux++;
      }
    }
    /*Multiplicacion*/
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          mmult[i][j]=m1n1[i][j]*m2n1[i][j];
      }
    }
    /*impresion*/
    printf("Matriz 1 (hijo):\n");
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          printf("%i ",m1n1[i][j]);
          if(j==9){
            printf("\n");
          }
      }
    }
    /*impresion*/
    printf("Matriz 2 (hijo):\n");
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          printf("%i ",m2n1[i][j]);
          if(j==9){
            printf("\n");
          }
      }
    }

    /*mandamos resultado al padre*/
    int contador_hijo_padre=0;
    for(int i=0;i<10;i++){
      for (int j =0;j<10;j++){
         buffer[2][contador_hijo_padre] = mmult[i][j];
         contador_hijo_padre++;
      }
    }


    /*escritura en buffer de hijo hacia nieto*/
    int m1buffer [10][10]={
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0,0,0},};
    //matriz 2
    int m2buffer [10][10]={
                        {0,2,0,1,3,3,0,3,2,0},
                        {1,0,3,2,3,0,1,5,4,1},
                        {0,1,0,2,3,3,0,3,2,0},
                        {1,0,0,2,3,3,0,3,2,2},
                        {1,2,3,4,3,0,1,5,4,1},
                        {1,0,2,0,3,3,0,3,5,0},
                        {1,1,3,2,3,0,1,3,0,2},
                        {3,0,5,2,3,3,0,3,2,2},
                        {0,2,2,3,3,6,1,0,5,2},
                        {0,1,2,2,3,3,0,3,2,2}};

    /*procedemos a llenar el buffer con las matrices que mandara el hijo-nieto*/
    int contador_hijo=0;
    for(int i=0;i<10;i++){
        for (int j = 0; j < 10; j++){
            buffer[1][contador_hijo] = m1buffer[i][j];
            contador_hijo++;
        }
    }

    for(int k=0;k<10;k++){
        for (int l = 0; l < 10; l++){
             buffer[1][contador_hijo] = m2buffer[k][l];
             contador_hijo++;
        }
    }

    /*creacion del proceso nieto*/
    if((idproc=fork())==0){
      printf("Soy el nieto\n");
      int m1n1 [10][10], m2n1 [10][10], msuma [10][10];
      int aux=0;
      /*llenamos las matrices y efectuamos suma*/
      for(int i=0;i<10;i++){
        for (int j = 0; j < 10; j++){
             m1n1[i][j]=buffer[1][aux];
             aux++;
        }
      }
      for(int l=0;l<10;l++){
        for (int m = 0; m < 10; m++){
             m2n1[l][m]=buffer[1][aux];
             aux++;
        }
      }
      /*Multiplicacion*/
      for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            msuma[i][j]=m1n1[i][j]+m2n1[i][j];
        }
      }
      /*impresion*/
      printf("Matriz 1 (nieto):\n");
      for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            printf("%i ",m1n1[i][j]);
            if(j==9){
              printf("\n");
            }
        }
      }
      /*impresion*/
      printf("Matriz 2 (nieto):\n");
      for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            printf("%i ",m2n1[i][j]);
            if(j==9){
              printf("\n");
            }
        }
      }

      /*mandamos resultado al abuelo*/
      int contador_nieto_padre=0;
      for(int i=0;i<10;i++){
        for (int j = 0; j < 10; j++){
           buffer[3][contador_nieto_padre] = msuma[i][j];
           contador_nieto_padre++;
        }
      }
      exit(0);
    }
    wait(0);
    exit(0);
  }
  wait(0);

  printf("Soy el padre.\n");
  /*imprimimos las matrices resultantes del hijo y nieto en padre*/
  int p1m1 [10][10], p1m2 [10][10];
  int contador_padre1,contador_padre2;
  for(int i=0;i<10;i++){
    for (int j = 0; j < 10; j++){
         p1m1[i][j]=buffer[3][contador_padre1];
         contador_padre1++;
    }
  }
  printf("Matriz suma nieto:\n");
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        printf("%i ",p1m1[i][j]);
        if(j==9){
          printf("\n");
        }
    }
  }
  for(int i=0;i<10;i++){
    for (int j = 0; j < 10; j++){
         p1m2[i][j]=buffer[2][contador_padre2];
         contador_padre2++;
    }
  }
  printf("Matriz multiplicacion hijo:\n");
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        printf("%i ",p1m2[i][j]);
        if(j==9){
          printf("\n");
        }
    }
  }

  float a[25][25],b[25][25];
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        a[i][j]=(float)p1m1[i][j];
    }
  }
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        b[i][j]=(float)p1m2[i][j];
    }
  }
  /*inversa de suma*/
  float k1=10, d1;
  d1 = determinante(a, k1);
  if (d1 == 0)
   printf("\nLa inversa de la matriz no es posible.\n");
  else{
   cofactor(a, k1);
   printf("Inversa de matriz resultado de suma:\n");
   LeeArchivoInv("/home/andres/Documents/s.o/O.S/p6/mtzinv1.txt");
  }
  /*inversa de multiplicacion*/
  float k2=10, d2;
  d2 = determinante(b, k2);
  if (d2 == 0)
   printf("\nLa inversa de la matriz no es posible.\n");
  else{
   cofactor(b, k2);
   printf("\nInversa de matriz resultado de multiplicacion:\n");
   LeeArchivoInv("/home/andres/Documents/s.o/O.S/p6/mtzinv2.txt");
  }
   return 0;
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
     CreaArchivoInv(inversa,"/home/andres/Documents/s.o/O.S/p6/mtzinv.txt");
}
