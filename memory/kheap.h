#ifndef KHEAP_H
#define KHEAP_H

#include <stddef.h>
#include <stdint.h>

void init_kheap(void);
void* kmalloc_dyn(size_t size);
void kfree(void* ptr);

#endif