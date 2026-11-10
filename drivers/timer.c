#include "sched/task.h"
#include "drivers/timer.h"
#include "cpu/isr.h"
#include "cpu/ports.h"

static uint32_t ticks = 0;
static uint32_t timer_freq = 100;

static void timer_callback(registers_t regs){
    ticks++;
    if(ticks%5==0) yield();
}

void init_timer(uint32_t frequency){
    timer_freq = frequency;
    register_interrupt_handler(32, timer_callback);
    uint32_t divisor = 1193180/frequency;
    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}

uint32_t get_ticks(void){
    return ticks;
}

void sleep_ms(uint32_t ms){
    uint32_t target_ticks = ticks + (ms*timer_freq)/1000;
    while(ticks < target_ticks){
        __asm__ volatile("hlt");
    }
}
