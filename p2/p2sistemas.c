#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int cp(const char *from, const char *to);


int main(int argc, char const *argv[]) {

/////////////////////////caso 1
  int op;
  char * cadena = NULL;
  char * cadena1 = NULL;
  int tamanio = 50;
  cadena = (char *)calloc(tamanio, sizeof(char));
  cadena1 = (char *)calloc(tamanio, sizeof(char));
////////////////////////caso2
  int fd;
  char c;

  do{
  printf("1.-Copiar archivo.\n");
  printf("2.-Abrir archivo.\n");
  printf("3.-Salir.\n\n");
  printf("Introduzca opcion: \n");

  scanf("%d",&op);

    switch (op) {
      case 1:
        //Leemos la direccion del archivo a abrir
        printf("Escriba la direccion y nombre del archivo a copiar: \n");
        printf("--Ejemplo: /home/ejemplo.txt --\n");
        scanf("%s",cadena);

        printf("Escriba la direccion destino y el nombre del archivo: \n");
        printf("--Ejemplo: /home/copia_ejemplo.txt --\n");
        scanf("%s",cadena1);

        int no=cp(cadena,cadena1);

        if(no==0)
          printf("Copiao\n");
        if(no==-1)
          printf("Error al abrir\n");
      break;


      case 2:
        printf("%s", "Escriba la direccion del directorio:");
        scanf("%s", cadena);

        fd = open(cadena,O_RDONLY);
        //Control de caso: existe archivo fd!=-1 o no fd=-1
        if(fd!=-1)
          {
            //Leemos el archivo
            //El archivo se lee caracter por caracter
            int i=0;
            while(read(fd,&c,sizeof(c)!=0)){
            printf("%c",c);
          }
            //Cerramos archivo
            close(fd);
          }
        else{
          printf("\nEl archivo no existe.\n");
        }
      break;
    }
  printf("\n\n");
  }while (op!=3);

  return 0;
}

int cp(const char *from, const char *to)
{

  int fd_to, fd_from;
      char buf[4096];
      ssize_t nread;
      int saved_errno;

      fd_from = open(from, O_RDONLY);
      if (fd_from < 0)
          return -1;

      fd_to = open(to, O_WRONLY | O_CREAT | O_EXCL, 0666);
      if (fd_to < 0)
          goto out_error;

      while (nread = read(fd_from, buf, sizeof buf), nread > 0)
      {
          char *out_ptr = buf;
          ssize_t nwritten;

          do {
              nwritten = write(fd_to, out_ptr, nread);

              if (nwritten >= 0)
              {
                  nread -= nwritten;
                  out_ptr += nwritten;
              }
              else if (errno != EINTR)
              {
                  goto out_error;
              }
          } while (nread > 0);
      }

      if (nread == 0)
      {
          if (close(fd_to) < 0)
          {
              fd_to = -1;
              goto out_error;
          }
          //copiado exitoso
          close(fd_from);
          return 0;
      }
      out_error:
      saved_errno = errno;

      close(fd_from);
      if (fd_to >= 0)
          close(fd_to);

      errno = saved_errno;
      return -1;
}
