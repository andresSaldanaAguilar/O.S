section	.text
   global _start        ;must be declared for using gcc

_start:	                ;tell linker entry point
   mov ecx,len          ;numero de iteraciones (longitud de la cadena)
   dec ecx              ;decrementamos el la longitud porque nos da uno mas de la longitud real
   mov eax, '1'         ;iniciamos la cuenta en uno

l1:

   push ecx ;guardamos en stack el valor de ecx
   mov [num], eax ;la posicion en el string num es igual a eax
   inc eax  ;incrementa
   pop ecx  ;recupera el ecx

   loop l1

   mov edx,1d ;tamaño
   mov ecx,num  ;imprimimos el ultimo numero
   mov ebx,1  ;salida estandar
   mov eax,4 ;sys_write

   int 0x80
   mov eax,1             ;system call number (sys_exit)
   int 0x80              ;call kernel


section	.bss
num resb 1  ;reserva un byte

section .data
msg db 'Helloooooo', 0xa  ;string to be printed
len equ $ - msg     ;length of the string
