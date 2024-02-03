[org 0x7c00]
mov ah, 0x0e
mov bx, HELLO_WORLD


print_string: mov al, [bx]
cmp al, 0
je END
int 0x10
add bx, 1
jmp print_string

HELLO_WORLD: 
    db 'HELLO WORLD', 0


END: 
    jmp $

TIMES 510 - ($-$$) db 0
dw 0xaa55
