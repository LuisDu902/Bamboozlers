#ifndef _TIMER_H_
#define _TIMER_H_

#include <lcom/lcf.h>

int (timer_set_frequency)(uint8_t timer, uint32_t freq);
int (timer_get_conf)(uint8_t timer, uint8_t *status);
int (timer_subscribe_interrupt)(uint32_t *timer_irq);
int (timer_unsubscribe_int)();

#endif
