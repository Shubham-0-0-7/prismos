[bits 32]

global inb
global outb
global inw
global outw
global io_wait

inb:
    mov dx, [esp+4]
    in al, dx
    movzx eax, al
    ret

outb: 
    mov dx, [esp+4]
    mov al, [esp+8]
    out dx, al
    ret

inw:
    mov dx, [esp+4]
    in ax, dx
    movzx eax, ax
    ret

outw:
    mov dx, [esp+4]
    mov ax, [esp+8]
    out dx, ax
    ret

io_wait:
    mov dx, 0x80
    mov al, 0
    out dx, al
    ret
