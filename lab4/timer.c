#include <lcom/lcf.h>
#include <stdint.h>
#include "timer.h"

int timer0_hook_id = TIMER0_IRQ;
uint8_t timer_counter = 0;

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = timer0_hook_id;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer0_hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&timer0_hook_id);
}

void (timer_int_handler)() {
  timer_counter++;
}
