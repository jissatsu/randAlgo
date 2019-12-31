section .data
    num  dw 2999
    divi dw 10

    index  dd 4
    result db 0
    remain db 0

    string: times 5 db 0

section .text
    global _start

_start:
    mov dx, 0x0000
    mov ax, word [num]
    mov ebx, dword [index]
itoaLoop:
    div word [divi]
    add dx, 48
    mov byte [string + ebx], dl
    xor dx, dx ; ============ zero the `dx` register
    sub ebx, 1
    cmp ax, 0
    jg itoaLoop
printItoa:
    mov rax, 1
    mov rdi, 1
    mov rsi, string
    mov rdx, 5
    syscall
exit:
    mov rax, 60
    mov rdi, 0
    syscall