print:
    pusha
    
    mov ah, 0x0e
    loop: 
        mov al, [bx]
        cmp al, 0
        je END
        int 0x10
        add bx, 1
        jmp loop
    
    END: 
        popa
        ret

print_ln:
    pusha

    mov al, '\n'
    int 0x10
    mov al, '\r'
    int 0x10
    
    popa
    ret