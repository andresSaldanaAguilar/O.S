

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/****************************************************************
Funciones auxiliares para inicializar, hacer wait y hacer Signal
Funcionan con arrays de semaforos, si solo hay uno ese parametro es 0
*******************************************************************/
void error(char* errorInfo) {
    fprintf(stderr,"%s",errorInfo);
    exit(1);
}
/*semaforo en verde*/
void doSignal(int semid, int numSem) {
    struct sembuf sops; //Signal
    sops.sem_num = numSem;
    sops.sem_op = 1;
    sops.sem_flg = 0;

    if (semop(semid, &sops, 1) == -1) {
        perror(NULL);
        error("Error al hacer Signal");
    }
}
/*semaforo en rojo*/
void doWait(int semid, int numSem) {
    struct sembuf sops;
    sops.sem_num = numSem; /* Sobre el primero, ... */
    sops.sem_op = -1; /* ... un wait (resto 1) */
    sops.sem_flg = 0;

    if (semop(semid, &sops, 1) == -1) {
        perror(NULL);
        error("Error al hacer el Wait");
    }
}

void initSem(int semid, int numSem, int valor) { //iniciar un semaforo

    //id del semaforo, indice del semaforo,valor es el valor con el que se inicializa
    if (semctl(semid, numSem, SETVAL, valor) < 0) {
    perror(NULL);
        error("Error iniciando semaforo");
    }
}


int main() {
    puts("Sincronizacion con Semaforos ");
    int semaforo;

    //1, numero de semaforos a crear
    if((semaforo=semget(IPC_PRIVATE,1,IPC_CREAT | 0700))<0) {
        perror(NULL);
        error("Semaforo: semget");
    }

    initSem(semaforo,0,1);
    puts("Hay una plaza libre");

switch (fork())
   {
    case -1:
        error("Error en el fork");


    case 0:  /* Hijo */
				/*el semaforo esta en rojo, esta ocupado*/
        doWait(semaforo,0);
        puts("Entro el hijo, el padre espera");
        sleep(5);
				/*el semaforo cambia a verde, esta libre*/
        puts("El hijo sale");
        doSignal(semaforo,0);
        exit(0);

    default: /* Padre */
				/*el semaforo esta en rojo, esta ocupado*/
        doWait(semaforo,0);
        puts("Entro el padre, el hijo espera");
        cadena="holi";
        sleep(5);
        puts("El padre sale");
				/*el semaforo cambia a verde, esta libre*/
        doSignal(semaforo,0);
    }

    sleep(10);

     //Liberacion del semaforo
     if ((semctl(semaforo, 0, IPC_RMID)) == -1) {
            perror(NULL);
            error("Error al borrar semaforo");
        }
    return 0;
}
