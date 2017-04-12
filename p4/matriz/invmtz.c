#include<stdio.h>
#include<math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "funcionesmtz.h"
#include <stdlib.h>

float determinante(float [][25], float);
void cofactor(float [][25], float);
void transpuesta(float [][25], float [][25], float);

int main(){
  float k=10, d;
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

  d = determinante(a, k);
  if (d == 0)
   printf("\nLa inversa de la matriz no es posible.\n");
  else
   cofactor(a, k);
}

/*Calculando el determinante de la matriz */
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
  transpuesta(num, fac, f);
}

/*Encontrando la transpuesta de la matriz*/

void transpuesta(float num[25][25], float fac[25][25], float r){
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
     CreaArchivoInv(inversa,"/home/andres/Documents/s.o/O.S/p4/matriz/msuma.txt");
     LeeArchivoInv("/home/andres/Documents/s.o/O.S/p4/matriz/msuma.txt");
}
