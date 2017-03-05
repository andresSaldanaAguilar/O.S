#include <stdio.h>

void hanoi(int n,int com, int aux, int fin);

main(){
       char com='A';
       char aux='B';
       char fin='C';
       int n;       
       printf("\nN£mero de discos: ");
       scanf("%d",&n);
       
       printf("\n\nLos movimientos a realizar son: \n");
       hanoi(n,com,aux,fin);

       
	   }
	   

void hanoi(int n,int com, int aux, int fin)
{
     if(n==1){
  		 printf("%c->%c",com,fin);
              }
     else{
                   hanoi(n-1,com,fin,aux);
                   printf("\n%c->%c\n",com,fin);
                   hanoi(n-1,aux,com,fin);
                  
                   }
                   
     }
