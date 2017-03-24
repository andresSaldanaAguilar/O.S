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
    push dx                         ; LIFO
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
    mov [uNum], eax

    xor edx, edx
    mov eax, [uNum]
    dec eax

    ; loop in order to save the length of the string

    mov ecx,promptLen    ;number of iterations (equal to the length of the string)
    l1:
    push ecx             ;guardamos en stack el valor de ecx
    mov [uNum], ebx      ;la posicion en el string num es igual a eax
    inc ebx              ;increment counter
    pop ecx              ;get back data
    loop l1

    ; end of loop

    mov [uNum], eax
    mov edi, num
    call eax2dec         
    mov [quotientLen], eax


    mov eax, 4
    mov ebx, 1
    mov ecx, prompt3
    mov edx, prompt3Len
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, num
    mov edx, [quotientLen]
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
