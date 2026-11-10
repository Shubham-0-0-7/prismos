#include "drivers/keyboard.h"
#include "sched/task.h"
#include "drivers/terminal.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "drivers/timer.h"
#include "memory/mem.h"
#include "shell/shell.h"
#include "lib/string.h"
#include "memory/paging.h"
#include "memory/pmm.h"
#include "memory/kheap.h"
#include "sched/task.h"

void main(){
    terminal_initialize();
    terminal_writestring("initializing prismOS\n");
    terminal_writestring("made with <3 by neocipher27...\n");

    idt_init();
    pic_remap();
    init_keyboard();
    init_timer(100);
    init_pmm(128*128*1024);

    init_paging();
    init_kheap();
    init_multitasking();
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
