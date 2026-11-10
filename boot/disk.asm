disk_load:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh

    mov cl, 0x02
    mov ch, 0x00

    mov dh, 0x00

    int 0x13
    jc disk_error

    pop dx
    cmp al, dh
    jne sector_error

    popa
    ret

disk_error:
    mov bx, DISK_ERR
    call print
    call print_nl
    mov dh, ah
    call print_hex
    jmp $

sector_error:
    mov bx, SECTOR_ERR 
    call print

SECTOR_ERR: db "incorrect no. of sectors read", 0 
DISK_ERR: db "error reading disk", 0 
