#include "memory/pmm.h"
#include "memory/mem.h"
#include "drivers/terminal.h"
#include <stdint.h>

static uint32_t* pmm_bitmap = 0;
static uint32_t pmm_total_pages = 0;
static uint32_t pmm_used_pages = 0;

static inline void bitmap_set(uint32_t bit){
    pmm_bitmap[bit/32] |= (1<<(bit%32));
}

static inline void bitmap_unset(uint32_t bit){
    pmm_bitmap[bit/32] &= ~(1<<(bit%32));
}

static inline int bitmap_test(uint32_t bit){
    return (pmm_bitmap[bit/32] & (1<<(bit%32)))!=0;
}

void init_pmm(uint32_t total_memory_bytes){
    pmm_total_pages = total_memory_bytes/PAGE_SIZE;
    uint32_t bitmap_size = (pmm_total_pages/8);

    pmm_bitmap = (uint32_t*)kmalloc_aligned(bitmap_size);
    memset(pmm_bitmap, 0, bitmap_size);

    for(uint32_t i=0; i<1024; i++){
        bitmap_set(i);
    }
    pmm_used_pages=1024;
    terminal_writestring("PMM: Bitmap initialized (128 MB RAM tracked)\n");
}

void* pmm_alloc_page(void){
    for(uint32_t i=0; i<pmm_total_pages; i++){
        if(!bitmap_test(i)){
            bitmap_set(i);
            pmm_used_pages++;
            return (void*)(i*PAGE_SIZE);
        }
    }
    return 0;
}

void pmm_free_page(void* page_addr){
    uint32_t page_index = ((uint32_t)page_addr)/PAGE_SIZE;
    if(bitmap_test(page_index)){
        bitmap_unset(page_index);
        pmm_used_pages--;
    }
}

uint32_t pmm_get_free_memory_kb(void){
    return (pmm_total_pages-pmm_used_pages)*4;
}