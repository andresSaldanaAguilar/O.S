// Archivo pila_parentesis.c
#include <stdio.h>
#include "pilaparentesis.h"

int verifica_balance(char expresion[], char cabre, char ccierra);

int main()
{
 char cadena[100];
 scanf("%s",cadena);

 int i=0;

 printf("La cadena a analizar es la siguiente:\n\n");
 while (cadena[i] != '\0')
       {
        printf("%c", cadena[i]);
        i++;
       }

 printf("\n\n");
 // Verifica si los paréntesis están balanceados
 if (verifica_balance(cadena, '(', ')') == 1)
     printf("Los paréntesis están balanceados\n");
 else
     printf("Los paréntesis NO están balanceados\n");
 // Verifica si los corchetes están balanceados
 if (verifica_balance(cadena, '[', ']') == 1)
     printf("Los corchetes están balanceados\n");
 else
     printf("Los corchetes NO están balanceados\n");
 // Verifica si las llaves están balanceadas
 if (verifica_balance(cadena, '{', '}') == 1)
     printf("Las llaves están balanceadas\n");
 else
     printf("Las llaves NO estan balanceadas\n");

 return 0;
}

int verifica_balance(char expresion[], char cabre, char ccierra)
{
 int x=0, balanceados=1;
 ptrPila pila = NULL; //Creamos la pila

 // Recorre la cadena
 while (expresion[x] != '0' && balanceados == 1)
       {
        //caso en que el caracter evaluado es un parentesis que abre
        if (expresion[x]==cabre)
            push(&pila, expresion[x]);
        else
            // caso en que el caracter evaluado es un parentesis que cierra
            if (expresion[x]==ccierra)
               {
                /* Si la pila está vacía, significa que los caracteres no están balanceados
                   porque se encontró un caracter que cierra sin que exista antes un caracter que abre
                */
                if (pila_vacia(&pila) != 1)
                    pop(&pila);
                else
                    balanceados = 0;
               }
        x++;
       }
 /* Si balanceados = 1 pero la pila no está vacía, los caracteres no están balanceados
    porque quedaron caracteres que abren sin tener su caracter que cierra
 */
 if (balanceados == 1 && pila_vacia(&pila) != 1)
     balanceados = 0;

 // Se asegura de dejar la pila vacia
 while (pila_vacia(&pila) != 1)
        pop(&pila);

 return balanceados;
}
