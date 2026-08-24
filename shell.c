#include "shell.h"
#include "string.h"
#include "terminal.h"
#include "timer.h"
#include "ports.h"
#include "mem.h"
#include <stdint.h>

void shell_init(void){
    terminal_writestring("\nType 'help' to see available commands.\n");
    terminal_writestring("neocipher27@prismOS ~$ ");
}

static void cmd_help(void){
    terminal_writestring("Available commands:\n");
    terminal_writestring("  help      - Show this help menu\n");
    terminal_writestring("  clear     - Clear the screen\n");
    terminal_writestring("  uptime    - Show system uptime in seconds\n");
    terminal_writestring("  pagefault - Trigger a CPU Page Fault Exception\n");
    terminal_writestring("  panic     - Trigger a Kernel Panic (Interrupt 0)\n");
    terminal_writestring("  reboot    - Restart the computer\n");
}

static void cmd_clear(void){
    terminal_initialize();
}

static void cmd_uptime(void){
    char buf[32];
    itoa(get_ticks()/100, buf, 10);
    terminal_writestring("Uptime: ");
    terminal_writestring(buf);
    terminal_writestring(" seconds\n");
}

static void cmd_reboot(void){
    terminal_writestring("Rebooting system ...\n");
    outb(0x64, 0xFE);
}

static void cmd_pagefault(void){
    terminal_writestring("Accessing unmapped memory at 0xA0000000..\n");
    uint32_t* unmapped_ptr = (uint32_t*)0xA0000000;
    uint32_t read_val = *unmapped_ptr;
    (void)read_val;
}

static void cmd_alloc(void){
    char buf[32];

    terminal_writestring("Current free_mem_addr before: 0x");
    itoa(get_free_mem_addr(), buf, 16);
    terminal_writestring(buf);
    terminal_writestring("\n");

    char* ptr=(char*)kmalloc(64);
    strcpy(ptr, "Nick's Placement allocator in action..");

    terminal_writestring("Allocated 64 bytes at: 0x");
    itoa((uint32_t)ptr, buf, 16);
    terminal_writestring(buf);
    terminal_writestring("\n");

    terminal_writestring("Data stored: \"");
    terminal_writestring(ptr);
    terminal_writestring("\"\n");

    terminal_writestring("free_mem_addr after: 0x");
    itoa(get_free_mem_addr(), buf, 16);
    terminal_writestring(buf);
    terminal_writestring("\n");
}

void shell_input(char* input){
    if(strlen(input)==0){
        terminal_writestring("neocipher27@prismOS ~$ ");
        return;
    }
    if(strcmp(input, "help")==0) cmd_help();
    else if(strcmp(input, "clear")==0) cmd_clear();
    else if(strcmp(input, "uptime")==0) cmd_uptime();
    else if(strcmp(input, "alloc")==0) cmd_alloc();
    else if(strcmp(input, "pagefault")==0) cmd_pagefault();
    else if(strcmp(input, "reboot")==0) cmd_reboot();
    else if(strcmp(input, "panic")==0) __asm__ volatile ("int $0");
    else{
        terminal_writestring("Unknown command!\n");
        cmd_help();
        terminal_writestring("\n");
    }
    terminal_writestring("neocipher27@prismOS ~$ ");
}

