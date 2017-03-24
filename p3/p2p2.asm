segment .bss
  cadena resb 50
  segment .text
  global _start

_start:
  mov edx,50d
  mov ecx,cadena
  mov ebx,0
  mov eax,3
  int 0x80
  mov ecx,50d
  mov edx,cadena
  mov eax,1
  mov ebx,4
  int 0x80
  mov eax,1
  int 0x80
