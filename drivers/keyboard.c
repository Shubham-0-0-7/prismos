#include "drivers/keyboard.h"
#include "cpu/ports.h"
#include "cpu/isr.h"
#include "drivers/terminal.h"
#include "shell/shell.h"

static char key_buf[256];
static int buf_idx = 0;

static const char scancode_ascii[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static void keyboard_callback(registers_t regs){
    uint8_t scancode = inb(0x60);
    if(scancode < sizeof(scancode_ascii)){
        char letter = scancode_ascii[scancode];
        if(letter == 0) return;
        if(letter == '\n'){
            terminal_putchar('\n');
            key_buf[buf_idx] = '\0';
            buf_idx = 0;
            shell_input(key_buf);
        }else if(letter == '\b'){
            if(buf_idx>0){
                buf_idx--;
                terminal_putchar('\b');
            }
        }else{
            if(buf_idx < 255){
                key_buf[buf_idx++]=letter;
                terminal_putchar(letter);
            }
        }
    }
}

void init_keyboard(void){
    register_interrupt_handler(33, keyboard_callback);
}