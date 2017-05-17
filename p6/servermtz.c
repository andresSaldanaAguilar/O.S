#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "funcionesmtz.h"
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h> /* shm*  */

#define FILEKEY "/bin/cat"
#define KEY 1301
#define MAXBUF 300

int main () {

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
   /* The daemon executes until press some character */
   printf ("Presiona --q-- para salir...\n");
   char c;
   c = getchar();



   /* Free the shared memory */
   shmdt ((char *)buffer);
   shmctl (zona_id, IPC_RMID, (struct shmid_ds *)NULL);
   return 0;
}
