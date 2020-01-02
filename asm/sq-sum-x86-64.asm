%define EXIT    0x3c
%define SUCCESS 0x00

%define WRITE   0x01
%define STDOUT  0x01

section .data
    n     db 1
    index db 3
    ddd   db 10
    sum   dw 0
    string: times 4 db 0x00

section .text
    global _start

_start:
    movzx ebx, BYTE [index]
squareSum:
    mov al, BYTE [n]
    mul al
    add WORD [sum], ax
    inc BYTE [n]
    cmp BYTE [n], 10
    jl squareSum
saveNum:
    mov ax, WORD [sum]
itoaNum:
    div BYTE [ddd]
    add ah, 48
    mov BYTE [ebx + string], ah
    ; reset `ah` register
    mov ah, 0x00
    dec ebx
    cmp al, 0
    jne itoaNum
printNum:
    mov rax, WRITE
    mov rdi, STDOUT
    mov rsi, string
    mov rdx, 4
    syscall
exit:
    mov rax, EXIT
    mov rdi, SUCCESS
    syscall
