#include <stdio.h>

int generar( int l);

 main (){
	int n,h;
	char reg;
	
	do{
	
	printf("Recuerde que debe de introducir el numero de asteriscos de la linea horizontal con mayor cantidad de ellos, que sea impar y multiplicado por un factor de dos.\n ");
	printf ("Introduzca el numero:\n");
	scanf ("%d",&n);
	h=((n/2)+1)%2;
		
		if (h==0){
			generar(n);	
		}
		else{
			printf("\t Lo sentios elnumero que ingreso no es impar y no podremos realizar sus rombos.\n\t Intentelo de nuevo.\n");
		
		}
	
	printf ("Desea regresar? \n Si=s\n No=n\n");
	scanf("%s", &reg);
	}while( (reg=='s')||(reg=='S'));

}

int generar(int l){
	int t=l/2;
	int x=0, y=0,a=0,b=0, tope1=((t/2)), tope2=((3*tope1)+1) , ban=0, taux=t/2;
	char m1[t][t];
	char m2[t][t];
	//--------------------Matriz 1 --------------
	for(y=0; y<t;y++){
		for(x=0; x<=t;x++){
			
			if (y<tope1){
				if (x==tope1-y){
					m1[y][x]='*';
					m2[y][x]='*';
				}
				else {
					m1[y][x]=' ';	
					m2[y][x]=' ';
				}
				m1[y][tope1+y]='*';
				m2[y][tope1+y]='*';
				for (b=tope1-y; b<=tope1+y;b++){
					m2[y][b]='*';
				}
			}
			
			else{
				if (x==ban){
					m1[y][x]='*';
					m2[y][x]='*';
				}
				else{
					m1[y][x]=' ';
					m2[y][x]=' ';
				}
				m1[y][(tope1)+taux]='*';
				m2[y][(tope1)+taux]='*';
				for (b=ban; b<=tope1+taux;b++){
					m2[y][b]='*';
				}
			}
		printf ("%c",m1[y][x]);	
		}
		for (a=0;a<=t;a++){
			
			printf ("%c",m2[y][a]);
		}
		if (y>=tope1){
				ban++;
				taux--;
			}
			
//------------------Relleno Matriz2-------------
		 

		printf ("\n");
	}
}
		
		
		
		
	
