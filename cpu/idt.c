#include "cpu/idt.h"

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

extern void *isr_stub_table[];
extern void *irq_stub_table[];

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].base_low = base & 0xFFFF;
  idt[num].base_high = (base >> 16) & 0xFFFF;
  idt[num].sel = sel;
  idt[num].always0 = 0;
  idt[num].flags = flags;
}

static inline void idt_flush(uint32_t idt_ptr_addr) {
  __asm__ volatile("lidt (%0)" : : "r"(idt_ptr_addr));
}

void idt_init(void) {
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base = (uint32_t)&idt;

  for (int i = 0; i < 256; i++) {
    idt_set_gate(i, 0, 0, 0);
  }

  for (int i = 0; i < 32; i++) {
    idt_set_gate(i, (uint32_t)isr_stub_table[i], 0x08, 0x8E);
  }
  for (int i = 0; i < 16; i++) {
    idt_set_gate(32 + i, (uint32_t)irq_stub_table[i], 0x08, 0x8E);
  }
  idt_flush((uint32_t)&idt_ptr);
}