#ifndef PMM_H
#define PMM_H

#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096

void init_pmm(uint32_t total_memory_bytes);
void* pmm_alloc_page(void);
void pmm_free_page(void* page_addr);
uint32_t pmm_get_free_memory_kb(void);

#endif