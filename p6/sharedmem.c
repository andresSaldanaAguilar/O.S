#include <sys/types.h> /*servidor de la memoria compartida, se ejecuta 1o*/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define TAM_MEM 27 /*tamanio de la memoria en bytes*/

int main(void){
  char c;
  int shmid;
  key_t llave;
  char *shm,*s;
  llave=5678;
  /*shmget retorna el id asociado al segmento de memoria asociado a la llave*/
  if((shmid=shmget(llave,TAM_MEM,IPC_CREAT|0666))<0){
    perror("Error al obtener la memoria compartida: shmget");
    exit(-1);
  }
  /*indicamos que queremos compartir*/
  if((shm=shmat(shmid,NULL,0))==(char*)-1){
    perror("Error al enlazar la memoria compartida: shmat");
    exit(-1);
  }
  s=shm;
  for(c='a';c<='z';c++)
   *s++=c;
  *s='\0';
  while(*shm!='*')
    sleep(1);
  exit(0);
}
