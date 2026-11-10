#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef struct task{
    uint32_t esp;
    uint32_t stack_bottom;
    struct task* next;
}task_t;

void init_multitasking(void);
void create_task(void (*entry_point)(void));
void yield(void);

void enable_preemption(void);
void disable_preemption(void);

#endif
