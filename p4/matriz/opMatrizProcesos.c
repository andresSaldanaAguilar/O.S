#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include<math.h>
#include <time.h>
#include "funcionesmtz.h"

void Suma(int m1 [10][10],int m2 [10][10]);
void Resta(int m1 [10][10],int m2 [10][10]);
void Imprime(int mtz [10][10]);
void Mltpn(int m1 [10][10],int m2 [10][10]);
void Transpuesta(int mtz [10][10]);
float determinante(float [][25], float);
void cofactor(float [][25], float);
void Transpuestainv(float [][25], float [][25], float);

int main(int argc, char const *argv[]) {
  //variables y constantes para matriz inversa
  float k=10, d;
  clock_t start_t, end_t;
  //matriz 1
  int m1 [10][10]={{0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2}};
  //matriz 2
  int m2 [10][10]={{0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2},
                   {0,1,2,3,3,2,1,0,1,2}};

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

  int idproc;
  start_t = clock();

  if((idproc=fork())==0){
    //Realiza Suma
    Suma(m1,m2);
  }
  else exit(0);
  if((idproc=fork())==0){
    //Realiza Resta
    Resta(m1,m2);
  }
  else exit(0);
  if((idproc=fork())==0){
    //Realiza Multiplicacion
    Mltpn(m1,m2);
  }
  else exit(0);
  if((idproc=fork())==0){
    //Realiza Transpuesta
    Transpuesta(m1);
  }
  else exit(0);
  if((idproc=fork())==0){
    //inversa de la matriz
    d = determinante(a, k);
    if (d == 0)
     printf("\nLa inversa de la matriz no es posible.\n");
    else
     cofactor(a, k);
  }
  else exit(0);
  if((idproc=fork())==0){
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
  }

  end_t = clock();
  double t = (float)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("\nTiempo tomado por la CPU: %f\n", t);

  return 0;
}

 void Suma (int m1 [10][10],int m2 [10][10]){
  int m3 [10][10];
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        m3[i][j]=m1[i][j]+m2[i][j];
    }
  }
  CreaArchivo(m3,"/home/andres/Documents/s.o/O.S/p4/matriz/msuma.txt");

}

void Resta(int m1 [10][10],int m2 [10][10]){
  int m3 [10][10];
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        m3[i][j]=m1[i][j]-m2[i][j];
    }
  }
  CreaArchivo(m3,"/home/andres/Documents/s.o/O.S/p4/matriz/mresta.txt");
  LeeArchivo("/home/andres/Documents/s.o/O.S/p4/matriz/mresta.txt");
}

void Mltpn(int m1 [10][10],int m2 [10][10]){
  int m3 [10][10];
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        m3[i][j]=m1[i][j]*m2[i][j];
    }
  }
  CreaArchivo(m3,"/home/andres/Documents/s.o/O.S/p4/matriz/mltp.txt");
  LeeArchivo("/home/andres/Documents/s.o/O.S/p4/matriz/mltp.txt");
}

void Transpuesta(int mtz [10][10]){
  int m3 [10][10];
  for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          m3[i][j]=mtz[j][i];
      }
  }
  CreaArchivo(m3,"/home/andres/Documents/s.o/O.S/p4/matriz/mtrp.txt");
  LeeArchivo("/home/andres/Documents/s.o/O.S/p4/matriz/mtrp.txt");
}

void Imprime(int mtz [10][10]){
  for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          printf("%d ",mtz[i][j]);
      }
    printf("\n");
  }
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
     LeeArchivoInv("/home/andres/Documents/s.o/O.S/p4/matriz/msinv.txt");
}
