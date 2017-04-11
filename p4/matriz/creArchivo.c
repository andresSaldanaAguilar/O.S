#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "pila.h"

int main(int argc, char const *argv[]) {

  char *fn="/home/andres/Documents/s.o/O.S/p4/matriz/create0.txt";
  int fd;

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

  char int2Str[1];
  char aux[10];
  char c;

  if ((fd = creat(fn, S_IRUSR | S_IWUSR)) < 0){
    perror("creat() error");
  }
  else {
    for (int i = 0;i<10;i++) {
        *aux='0';
        *int2Str='0';
        for(int j=0;j<10;j++){
          c=m1[i][j]+'0';
          sprintf(int2Str,"%c",c);
          write(fd,int2Str,sizeof(int2Str));
        }
    }
        close(fd);
  }
return 0;
}
