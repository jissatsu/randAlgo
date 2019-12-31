section .data
    num  dw 2999
    divi dw 10

    index  db 4
    result db 0
    remain db 0

    string: times 5 db 0

section .text
    global _start

_start:
    mov dx, 0x0000
    mov ax, word [num]
    movzx ebx, byte [index]
itoaLoop:
    div word [divi]
    add dx, 48
    mov byte [string + ebx], dl
    xor dx, dx ; ============ zero the `dx` register
    sub ebx, 1
    cmp ax, 0
    jg itoaLoop
printItoa:
    mov eax, 4
    mov ebx, 1
    mov ecx, string
    mov edx, 5
    int 0x80
exit:
    mov eax, 1
    mov ebx, 0
    int 0x80
