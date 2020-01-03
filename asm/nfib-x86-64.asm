; find the n-th fibonacci number

%define SYSEXIT  0x3c
%define SUCCESS  0x00

%define SYSWRITE 0x01
%define STDOUT   0x01

section .data
    n    db 8
    n1   db 0
    ddd  db 10
    num: times 3 db 0x00
    ; sequence
    fib: db 0, 1, 1, 2, 3, 5, 8, 13, 21, 34

section .text
    global _start

_start:
    cmp BYTE [n], 1
    jle ZeroOrOne
    movzx esi, BYTE [n]
    
    mov al, BYTE [(esi - 1) + fib]
    mov BYTE [n1], al

    mov al, BYTE [(esi - 2) + fib]
    add al, BYTE [n1]
    ; `esi` -> pointer to the last element of `num`
    mov esi, 0x00000002
itoaNum:
    mov ah, 0x00
    div byte [ddd]
    add ah, 48
    mov BYTE [esi + num], ah
    dec esi
    cmp al, 0x00
    jne itoaNum
    jmp printNum
ZeroOrOne:
    mov al, BYTE [n]
    add al, 48
    mov BYTE [num], al
    jmp printNum
printNum:
    lea rbx, BYTE [num]
    mov rax, SYSWRITE
    mov rdi, STDOUT
    mov rsi, rbx
    mov rdx, 3
    syscall
exit:
    mov rax, SYSEXIT
    mov rdi, SUCCESS
    syscall