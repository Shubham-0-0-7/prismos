# my-os

## layout

```
boot/     16-bit bootloader: disk load, GDT, switch to protected mode
kernel/   kernel entry stub + main()
cpu/      IDT, ISR/IRQ stubs, PIC, port I/O
drivers/  VGA text terminal, PS/2 keyboard, PIT timer
memory/   bump allocator, physical page bitmap, paging, kernel heap
sched/    tasks + context switch
lib/      string helpers
shell/    built-in shell commands
```

`make` builds into `build/`, `make run` boots it in QEMU.

## status 6 september 2026   

<img width="472" height="344" alt="image" src="https://github.com/user-attachments/assets/db36423c-7594-400c-bffb-d894b04cbe6e" />



## status 21 august 2026

<img width="472" height="344" alt="image" src="https://github.com/user-attachments/assets/420d3884-9e56-47e8-8f16-612fe71598a8" />

## status 29 july 2026

<img width="472" height="344" alt="image" src="https://github.com/user-attachments/assets/f25c557a-fe4b-4209-8c2c-946fcdffab5e" />    


<img width="1470" height="956" alt="image" src="https://github.com/user-attachments/assets/96c3e069-8b85-40e3-850a-022b996060e5" />    



## status 24 july 2026

<img width="472" height="344" alt="Screenshot 2026-07-24 at 01 24 46" src="https://github.com/user-attachments/assets/3fe456be-8187-4b09-b0fe-74145845c128" />   

<img width="1470" height="956" alt="Screenshot 2026-07-24 at 01 28 53" src="https://github.com/user-attachments/assets/ab4b9aba-287b-4d97-bad3-25763cae1eb0" />    

## status 21 july 2026
<img width="472" height="344" alt="Screenshot 2026-07-21 at 11 53 45" src="https://github.com/user-attachments/assets/e3fdc3da-9ece-4a62-b767-746df1ff628c" />   

<img width="1470" height="923" alt="Screenshot 2026-07-21 at 12 03 58" src="https://github.com/user-attachments/assets/812bc78d-c5de-4392-9c87-1923a800732d" />




