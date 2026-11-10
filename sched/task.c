#include "sched/task.h"
#include "memory/kheap.h"
#include "drivers/terminal.h"

extern void switch_task(uint32_t* old_esp, uint32_t new_esp);

static task_t* current_task = 0;
static task_t* task_list = 0;

static int preemption_enabled = 0;

void init_multitasking(void){
    current_task = (task_t*)kmalloc_dyn(sizeof(task_t));
    current_task->esp = 0;
    current_task->stack_bottom = 0;
    current_task->next = current_task;
    task_list = current_task;

    terminal_writestring("\nCooperative Multitasking initialized\n");
}

void create_task(void (*entry_point)(void)){
    task_t* new_task = (task_t*)kmalloc_dyn(sizeof(task_t));
    uint32_t stack = (uint32_t)kmalloc_dyn(4096);
    uint32_t* stack_top = (uint32_t*)(stack+4096);

    *(--stack_top)=(uint32_t)entry_point;
    *(--stack_top)=0x0202;
    *(--stack_top)=0;
    *(--stack_top)=0;
    *(--stack_top)=0;
    *(--stack_top)=0;
    *(--stack_top)=0;
    *(--stack_top)=0;
    *(--stack_top)=0;
    *(--stack_top)=0;
    
    new_task->esp = (uint32_t)stack_top;
    new_task->stack_bottom = stack;

    new_task->next = task_list->next;
    task_list->next = new_task;
}

void yield(void){
    if(!current_task || current_task == current_task->next) return;

    task_t* last_task = current_task;
    current_task = current_task->next;

    switch_task(&last_task->esp, current_task->esp);
}

void enable_preemption(void){
    preemption_enabled = 1;
}

void disable_preemption(void){
    preemption_enabled = 0;
}