section	.text
   global _start        ;must be declared for using gcc

_start:	                
   mov ecx,9            ;numero de iteraciones (longitud de la cadena)
   mov eax, '1'         ;iniciamos la cuenta en uno

l1:

   push ecx 		;guardamos en stack el valor de ecx
   mov edx, 1d ;tamaño
   mov [num], eax 	;la posicion en el string num es igual a eax
   mov ecx, num 	; mandamos como parametro el numero, que se imprime en pantalla  ecx<-num
   mov ebx, 1 		;salida estandar
   mov eax, 4 		;sis_write
   int 0x80

   mov eax, [num]  	;eax<-num
   inc eax 	        ;incrementa
   pop ecx 	        ;recupera el ecx

   loop l1

   mov eax,1             ;sys_exit
   int 0x80              


section	.bss
num resb 1  ;reserva un byte

