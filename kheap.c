#include "kheap.h"
#include "terminal.h"

typedef struct header{
    size_t size;
    int is_free;
    struct header* next;
} header_t;

#define HEAP_START 0x180000
#define HEAP_SIZE (2*1024*1024)

static header_t* head = (header_t*)HEAP_START;

void init_kheap(void){
    head->size = HEAP_SIZE - sizeof(header_t);
    head->is_free = 1;
    head->next = 0;
    terminal_writestring("Kernel Heap: Initialized (2MB with kfree & coalescing)");
}

void* kmalloc_dyn(size_t size){
    size = (size+3) & ~3;
    header_t* curr = head;
    while(curr){
        if(curr->is_free && curr->size >= size){
            if(curr->size >= size + sizeof(header_t)+4){
                header_t* new_block = (header_t*)((uint8_t*)curr + sizeof(header_t) + size);
                new_block->size = curr->size - size - sizeof(header_t);
                new_block->is_free = 1;
                new_block->next = curr->next;

                curr->size = size;
                curr->next = new_block;
            }
            curr->is_free = 0;
            return (void*)((uint8_t*)curr + sizeof(header_t));
        }
        curr = curr->next;
    }
    return 0;
}

void kfree(void* ptr){
    if(!ptr) return;
    header_t* block = (header_t*)((uint8_t*)ptr - sizeof(header_t));
    block->is_free = 1;

    header_t* curr = head;
    while(curr && curr->next){
        if(curr->is_free && curr->next->is_free){
            curr->size += sizeof(header_t) + curr->next->size;
            curr->next = curr->next->next;
        }else{
            curr = curr->next;
        }
    }
}