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
#define KEY 1301
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

   /* Key to shared memory */
   int key = ftok(FILEKEY, KEY);
   if (key == -1) {
      fprintf (stderr, "Error en la llave.\n");
      return -1;
   }

   /* we create the shared memory */
   int zona_id = shmget (key, sizeof(int)*MAXBUF, 0777 | IPC_CREAT);
   if (zona_id == -1) {
      fprintf (stderr, "Error en la zona_id.\n");
      return -1;
   }

   printf ("Zona ID de la memoria compartida: %i\n", zona_id);

   int *buffer; /* shared buffer */
   /* we declared to zone to share */
   buffer = shmat (zona_id, (char *)0, 0);
   if (buffer == NULL) {
      fprintf (stderr, "Error reservando memoria.\n");
      return -1;
   }


   printf ("Apuntador a buffer: %p\n", buffer);



  /*empezamos con el manejo de los procesos*/

  /*procedemos a llenar el buffer con las matrices*/
  int contador=0;
  for(int i=0;i<10;i++){
    for (int j = 0; j < 10; j++){
       buffer[contador] = m1[i][j];
       contador++;
    }
  }
  //printf("%i\n",contador);
  /*indice final de m1*/
  for(int k=0;k<10;k++){
    for (int l = 0; l < 10; l++){
       buffer[contador] = m2[k][l];
       contador++;
    }
  }
  //printf("%i\n",contador);
  /*indice final de m2*/

  int idproc;
  if((idproc=fork())==0){
    for(int i=0;i<200;i++){
    printf("%i",buffer[i]);
    }
    /*escritura en buffer*/
    if((idproc=fork())==0){
      /*lectura en buffer*/
    }
    exit(0);
  }
  wait(0);



   return 0;
}
