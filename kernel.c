#include "keyboard.h"
#include "terminal.h"
#include "idt.h"
#include "pic.h"
#include "timer.h"
#include "mem.h"
#include "shell.h"
#include "string.h"
#include "paging.h"

void main(){
    terminal_initialize();
    terminal_writestring("initializing prismOS\n");
    terminal_writestring("made with <3 by neocipher27...\n");

    idt_init();
    pic_remap();
    init_keyboard();
    init_timer(100);

    init_paging();
    __asm__ volatile("sti");
    // terminal_writestring("waiting 3 secs...");
    // sleep_ms(3000);
    // terminal_writestring("3 seconds done! ... timer works\n");

    // char* buf = (char*)kmalloc(100);
    // memcpy(buf, "dynamic memory allocation via kmalloc works!\n", sizeof("dynamic memory allocation via kmalloc works!\n"));
    // terminal_writestring(buf);
    // terminal_writestring("type something below... \n");
    shell_init();
}
