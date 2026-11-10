#include "memory/paging.h"
#include "cpu/isr.h"
#include "memory/mem.h"
#include "drivers/terminal.h"
#include "lib/string.h"

static uint32_t* page_directory=0;
static uint32_t* first_page_table=0;

void page_fault_handler(registers_t regs){
    uint32_t faulting_address;
    __asm__ volatile ("mov %%cr2, %0" : "=r" (faulting_address));
    int present = !(regs.err_code & 0x1);
    int rw = regs.err_code & 0x2;
    int us = regs.err_code & 0x4;
    int reserved = regs.err_code & 0x8;

    terminal_writestring("\n---[ KERNEL PAGE FAULT ]---\n");
    terminal_writestring("faulting address: 0x");
    char buf[32];
    itoa(faulting_address, buf, 16);
    terminal_writestring(buf);
    terminal_writestring("\nreason");

    if(present) terminal_writestring("[Page-Not-Present] ");
    if(rw) terminal_writestring("[Write-Violation] ");
    else terminal_writestring("[Read-Violation] ");
    if(us) terminal_writestring("[User-Mode] ");
    else terminal_writestring("[Kernel-Mode] ");
    if(reserved) terminal_writestring("[Reserved-Bits] ");
    terminal_writestring("\nSystem Halted!\n");

    for(;;){
        __asm__ volatile ("hlt");
    }
}

void init_paging(void){
    register_interrupt_handler(14, page_fault_handler);
    page_directory=(uint32_t*)kmalloc_aligned(1024*sizeof(uint32_t));
    first_page_table=(uint32_t*)kmalloc_aligned(1024*sizeof(uint32_t));

    for(uint32_t i=0; i<1024; i++){
        first_page_table[i]=(i*0x1000) | 3;
    }

    page_directory[0]=((uint32_t)first_page_table) | 3;
    for(uint32_t i=1; i<1024; i++) page_directory[i]=0x02;

    __asm__ volatile ("mov %0, %%cr3" : : "r" (page_directory));
    uint32_t cr0;

    __asm__ volatile ("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= 0x80000000; //bit 31:pg(paging enable)
    __asm__ volatile ("mov %0, %%cr0" : : "r" (cr0));
    
    terminal_writestring("virtual memory and paging: enabled (0-4MB identity mapped)\n");
}