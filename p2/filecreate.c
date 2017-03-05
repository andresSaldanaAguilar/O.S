#define _POSIX_SOURCE
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>
#include <string.h>

int main() {

  char *fn[3];
  fn[0]="C:\Users\ANDRES\Documents\create0.txt";
  fn[1]="C:\Users\ANDRES\Documents\create1.txt";
  fn[2]="C:\Users\ANDRES\Documents\create2.txt";
  int fd[2];
  char text[]="Carpe diem es una locución latina.";

  for (int i=0;i<3;i++) {
    if ((fd[i] = creat(fn[i], S_IRUSR | S_IWUSR)) < 0)
      perror("creat() error");
    else {
      write(fd[i],text,strlen(text));
      close(fd[i]);
      //unlink(fn);
    }
  }
return 0;
}
