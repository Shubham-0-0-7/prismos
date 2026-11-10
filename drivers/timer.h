#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void init_timer(uint32_t frequency);
void sleep_ms(uint32_t ms);
uint32_t get_ticks(void);

#endif
