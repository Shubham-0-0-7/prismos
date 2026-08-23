CC = i686-elf-gcc
LD = i686-elf-ld
CFLAGS = -ffreestanding -c
all: os-image.bin
run: os-image.bin
	qemu-system-x86_64 -drive file=os-image.bin,format=raw,index=0,media=disk

os-image.bin: main.bin kernel.bin
	cat main.bin kernel.bin > os-image.bin
	truncate -s 1474560 os-image.bin

main.bin: main.asm print.asm print-hex.asm disk.asm gdt-32bit.asm switch.asm print-32bit.asm
	nasm -f bin main.asm -o main.bin

kernel_entry.o: kernel_entry.asm
	nasm -f elf32 $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) $< -o $@

kernel.bin: kernel_entry.o kernel.o terminal.o ports.o idt.o isr.o interrupt.o pic.o keyboard.o timer.o mem.o string.o shell.o paging.o
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

paging.o: paging.c
	$(CC) $(CFLAGS) $< -o $@

timer.o: timer.c
	$(CC) $(CFLAGS) $< -o $@

pic.o: pic.c
	$(CC) $(CFLAGS) $< -o $@

keyboard.o: keyboard.c
	$(CC) $(CFLAGS) $< -o $@

idt.o: idt.c
	$(CC) $(CFLAGS) $< -o $@

isr.o: isr.c
	$(CC) $(CFLAGS) $< -o $@

interrupt.o: interrupt.asm
	nasm -f elf32 $< -o $@

terminal.o: terminal.c
	$(CC) $(CFLAGS) $< -o $@

ports.o: ports.asm
	nasm -f elf32 $< -o $@

mem.o: mem.c
	$(CC) $(CFLAGS) $< -o $@

string.o: string.c
	$(CC) $(CFLAGS) $< -o $@

shell.o: shell.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.bin *.o os-image.bin
