#include <stdio.h>
#include <stdlib.h>

void Suma(int m1 [10][10],int m2 [10][10]);
void Resta(int m1 [10][10],int m2 [10][10]);
void Imprime(int mtz [10][10]);
void Mltpn(int m1 [10][10],int m2 [10][10]);
void Transpuesta(int mtz [10][10]);

int main(int argc, char const *argv[]) {
  //matriz 1
  int m1 [10][10]={{0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9}};
  //matriz 2
  int m2 [10][10]={{0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9},
                   {0,1,2,3,4,5,6,7,8,9}};


  //imprime la matriz 1
  Imprime(m1);
  printf("\n");

  //imprime la matriz 2
  Imprime(m2);
  printf("\n");

  //Realiza Suma
  Suma(m1,m2);
  printf("\n");

  //Realiza Resta
  Resta(m1,m2);
  printf("\n");

  //Realiza Multiplicacion
  Mltpn(m1,m2);
  printf("\n");

  //Realiza Transpuesta
  Transpuesta(m1);
  printf("\n");



  return 0;
}

void Suma(int m1 [10][10],int m2 [10][10]){
  int m3 [10][10];
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        m3[i][j]=m1[i][j]+m2[i][j];
        printf("%d ",m3[i][j]);
    }
    printf("\n");
  }
}

void Resta(int m1 [10][10],int m2 [10][10]){
  int m3 [10][10];
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        m3[i][j]=m1[i][j]-m2[i][j];
        printf("%d ",m3[i][j]);
    }
    printf("\n");
  }
}

void Mltpn(int m1 [10][10],int m2 [10][10]){
  int m3 [10][10];
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
        m3[i][j]=m1[i][j]*m2[i][j];
        printf("%d ",m3[i][j]);
    }
    printf("\n");
  }
}

void Transpuesta(int mtz [10][10]){
  for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          printf("%d ",mtz[j][i]);
      }
    printf("\n");
  }
}

void Imprime(int mtz [10][10]){
  for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          printf("%d ",mtz[i][j]);
      }
    printf("\n");
  }
}
