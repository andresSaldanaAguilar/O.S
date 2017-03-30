#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
  int idproc,x=10,y=15,z=5;
  if((idproc=fork())==0){
      y+=z;
      printf("y: %i\n",y);
        if((idproc=fork())==0){
            z*=x;
            if((idproc=fork())==0){
              x-=z;
              printf("x: %i\n",x);
            }
            y+=x;
            printf("y: %i\n",y);
            if((idproc=fork())==0){
              z*=y;
              printf("z: %i\n",z);
            }
            if((idproc=fork())==0){
              x*=y;
              printf("x: %i\n",x);
            }
            printf("x: %i, y:%i, z:%i\n",x,y,z);
        }
        z-=x;
        if((idproc=fork())==0){
          y-=z;
          printf("y: %i\n",y);
        }
        if((idproc=fork())==0){
          x+=y;
          printf("x: %i\n",x);
          exit(0);
        }
        if((idproc=fork())==0){
          z*=x;
          printf("z: %i\n",z);
        }
  }
  printf("x: %i,y: %i,z: %i\n",x,y,z);
  exit(0);
}
