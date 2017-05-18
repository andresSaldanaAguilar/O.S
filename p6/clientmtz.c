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
#include <sys/shm.h> /* shm*  */

#define FILEKEY "/bin/cat"

#define MAXBUF 300

int main (void) {

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
                   {0,1,2,3,3,2,1,0,1,5}};

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

  /*procedemos a llenar el buffer con las matrices*/
  int contador_padre=0;
  for(int i=0;i<10;i++){
    for (int j = 0; j < 10; j++){
       buffer[1][contador_padre] = m1[i][j];
       contador_padre++;
    }
  }
  printf("%i\n",contador_padre);
  /*indice final de m1*/
  for(int k=0;k<10;k++){
    for (int l = 0; l < 10; l++){
       buffer[1][contador_padre] = m2[k][l];
       contador_padre++;
    }
  }
  printf("%i\n",contador_padre);
  /*indice final de m2*/

  int idproc;
  if((idproc=fork())==0){

    int m1h1 [10][10], m2h1 [10][10], msuma [10][10];
    int aux=0;
    /*llenamos las matrices y efectuamos suma*/
    for(int i=0;i<10;i++){
      for (int j = 0; j < 10; j++){
           m1h1[i][j]=buffer[1][aux];
           aux++;
      }
    }
    for(int l=0;l<10;l++){
      for (int m = 0; m < 10; m++){
           m2h1[l][m]=buffer[1][aux];
           aux++;
      }
    }
    /*suma*/
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          msuma[i][j]=m1h1[i][j]*m2h1[i][j];
      }
    }
    /*impresion*/
    printf("Matriz 1:\n");
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          printf("%i ",m1h1[i][j]);
          if(j==9){
            printf("\n");
          }
      }
    }
    /*impresion*/
    printf("Matriz 2:\n");
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          printf("%i ",m2h1[i][j]);
          if(j==9){
            printf("\n");
          }
      }
    }
    /*impresion*/
    printf("Matriz suma:\n");
    for(int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          printf("%i ",msuma[i][j]);
          if(j==9){
            printf("\n");
          }
      }
    }


    /*escritura en buffer*/
    //if((idproc=fork())==0){
      /*lectura en buffer*/
    //}
    exit(0);
  }
  wait(0);



   return 0;
}
