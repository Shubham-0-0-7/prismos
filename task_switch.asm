[bits 32]
global switch_task

switch_task:
    pusha
    pushf

    mov eax, [esp+40]
    mov [eax], esp

    mov esp, [esp+44]

    popf
    popa

    ret 