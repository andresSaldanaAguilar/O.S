segment .data
cadena db 'Programando en ensabladore :B',0xA
segment .text
global _start
_start:
  mov edx,30d
  mov ecx,cadena
  mov ebx,1
  mov eax,4
  int 0x80
  mov eax,1
  int 0x80
