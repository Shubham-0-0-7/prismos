#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include "cpu/isr.h"

void init_paging(void);
void page_fault_handler(registers_t regs);

#endif