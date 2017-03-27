segment .data
    prompt db "Ingrese cadena: "
    promptLen equ $-prompt
    prompt3 db 10, "Longitud de la cadena: "
    prompt3Len equ $-prompt3
    linefeed db 10

segment .bss

    num resb 80  ;reserva un byte
    inputNum resb 80
    uNum resd 1
    uQuo resd 1
    quotient resb 80
    quotientLen resd 1

segment .text

global _start

eax2dec:                            ; Arg EDI: Pointer to string that gets ASCII-characters
    mov ebx, 10                     ; Divisor
    xor ecx, ecx                    ; CX=0 (number of digits)

    .first_loop:
    xor edx, edx                    ; Attention: DIV applies also DX!
    div ebx                         ; DX:AX / BX = AX remainder: DX
    push dx                         ; LIFO, 16 bits
    inc cl                          ; Increment number of digits
    test eax, eax                   ; AX = 0?
    jnz .first_loop                 ; No: once more

    mov ebx, ecx                    ; Save strlen

    .second_loop:
    pop ax                          ; Get back pushed digit
    or al, 00110000b                ; AL to ASCII
    mov byte [edi], al              ; Save AL
    inc edi                         ; DI points to next character in string DECIMAL
    loop .second_loop               ; Until there are no digits left

    mov byte [edi], 0               ; End-of-string delimiter (ASCIZ)
    mov eax, ebx                    ; Return strlen in EAX
    ret

_start:

    mov eax, 4 ;sys_write
    mov ebx, 1
    mov ecx, prompt
    mov edx, promptLen
    int 80h

    mov eax, 3 ;sys_read
    mov ebx, 0
    mov ecx, inputNum
    mov edx, 80
    int 80h

    mov esi, inputNum
    mov [uNum], eax ;indice de la cadena
    dec eax ;decrementamos la posicion del indice (-1)

            ; loop in order to know the length of the string
    l1:
    mov [uNum], ebx      ;la posicion en el string num es igual a eax
    inc ebx              ;increment counter
    loop l1
            ; end of loop

    mov edi, num ;guardamos en num el indice una vez que se termino la iteracion
    call eax2dec

    mov eax, 4
    mov ebx, 1
    mov ecx, prompt3
    mov edx, prompt3Len
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, num
    ;mov edx, quotientLen
    int 80h

    ;solo para que se vea mas prou :B
    mov eax, 4
    mov ebx, 1
    mov ecx, linefeed
    mov edx, 1
    int 80h

    jmp exit

    exit:

    mov eax, 1
    xor ebx, ebx
    int 80h
