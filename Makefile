CC = i686-elf-gcc
LD = i686-elf-ld
AS = nasm
CFLAGS = -ffreestanding -I. -MMD -MP -c

BUILD = build

# kernel_entry must stay first: the bootloader jumps to the start of kernel.bin
KERNEL_OBJS = \
	kernel/kernel_entry.o \
	kernel/kernel.o \
	drivers/terminal.o \
	cpu/ports.o \
	cpu/idt.o \
	cpu/isr.o \
	cpu/interrupt.o \
	cpu/pic.o \
	drivers/keyboard.o \
	drivers/timer.o \
	memory/mem.o \
	lib/string.o \
	shell/shell.o \
	memory/paging.o \
	memory/pmm.o \
	memory/kheap.o \
	sched/task.o \
	sched/task_switch.o

OBJS = $(addprefix $(BUILD)/,$(KERNEL_OBJS))
BOOT_SRCS = $(wildcard boot/*.asm)

all: $(BUILD)/os-image.bin

run: $(BUILD)/os-image.bin
	qemu-system-x86_64 -drive file=$<,format=raw,index=0,media=disk

$(BUILD)/os-image.bin: $(BUILD)/main.bin $(BUILD)/kernel.bin
	cat $^ > $@
	truncate -s 1474560 $@

$(BUILD)/main.bin: $(BOOT_SRCS)
	@mkdir -p $(dir $@)
	$(AS) -f bin -i boot/ boot/main.asm -o $@

$(BUILD)/kernel.bin: $(OBJS)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

clean:
	rm -rf $(BUILD)

.PHONY: all run clean

-include $(OBJS:.o=.d)
