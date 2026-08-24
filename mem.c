#include "mem.h"
#include <stdint.h>
static uint32_t free_mem_addr = 0x100000;

void* memset(void* dest, int val, size_t count){
    uint8_t* temp = (uint8_t*)dest;
    for(size_t i=0; i<count; i++){
        temp[i]=(uint8_t)val;

    }
    return dest;
}


void* memcpy(void* dest, const void* src, size_t count){
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;
    for(size_t i=0; i<count; i++){
        d[i]=s[i];
    }
    return dest;
}

int memcmp(const void* s1, const void* s2, size_t count){
    const uint8_t* p1 = (const uint8_t*)s1;
    const uint8_t* p2 = (const uint8_t*)s2;
    for(size_t i=0; i<count; i++){
        if(p1[i]!=p2[i]){
            return p1[i]-p2[i];
        }
    }
    return 0;
}

void* kmalloc(size_t size){
    void* ret = (void*)free_mem_addr;
    free_mem_addr += size;
    return ret;
}

void* kmalloc_aligned(size_t size){
    if((free_mem_addr & 0xFFFFF000) != free_mem_addr){
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    void* ret = (void*)free_mem_addr;
    free_mem_addr += size;
    return ret;
}

uint32_t get_free_mem_addr(void){
    return free_mem_addr;
}