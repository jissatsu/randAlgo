section .data
    n1   db 0
    n2   db 0
    num  db 0

    _size    equ 10
    sys_exit equ 0x3c
    success  equ 0x00

    arr: db 5, 1, 8, 3, 4, 2, 6, 9, 7, 0

section .text
    global _start

_start:
    mov rsi, 0
    mov rcx, 0
    mov r8d, 0
    jmp inner
swap:
    mov al, byte [n1]
    mov bl, byte [n2]
    
    mov byte [arr + rsi], al
    mov byte [arr + (rsi - 1)], bl
    jmp inner

reset:
    xor rsi, rsi
    inc rcx
    cmp rcx, _size - 1
    jg printArr

inner:
    cmp rsi, _size - 2
    jg reset

    mov al, byte [arr + rsi]
    mov byte [n1], al

    mov al, byte [arr + (rsi + 1)]
    mov byte [n2], al
    
    inc rsi
    cmp byte [n1], al
    jg swap
    jmp inner

printArr:
    mov al, byte [arr + r8d]
    add al, 48
    mov byte [num], al

    lea rbx, byte [num]
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 1
    syscall

    inc r8d
    cmp r8d, _size - 1
    jle printArr
exit:
    mov rax, sys_exit
    mov rdi, success
    syscall