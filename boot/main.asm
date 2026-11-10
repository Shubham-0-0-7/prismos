[org 0x7c00]
KERNEL_OFFSET equ 0x1000
    xor ax, ax
    mov ds, ax
    mov es, ax

    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print
    call print_nl 
    call load_kernel

    call switch_to_pm
    jmp $

load_kernel:
    mov bx, KERNEL_OFFSET
    mov dh, 30
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret
    
%include "print.asm"
%include "print-hex.asm"
%include "disk.asm"

%include "gdt-32bit.asm"
%include "switch.asm"
%include "print-32bit.asm"

[bits 32]
BEGIN_PM:
      mov ebx, MSG_PROT_MODE
      call print_string_pm

      call KERNEL_OFFSET
      jmp $

MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0 
BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xaa55
