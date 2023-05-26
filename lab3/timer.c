#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int hook_id_timer = TIMER0_IRQ;
uint32_t timer_counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  if (!(timer == 0 || timer == 1 || timer == 2)) return 1;

  if (freq < 19 ||freq > TIMER_FREQ) return 1;

  uint16_t counter = TIMER_FREQ / freq;

  uint8_t LSB, MSB;

  util_get_LSB(counter, &LSB);
  util_get_MSB(counter, &MSB);

  uint8_t config;
  if (timer_get_conf(timer, &config) != 0) return 1;

  config &= 0xF;

  config |= TIMER_LSB_MSB; //config | = BIT(4) | BIT(5); -> LSB followed by MSB

  switch (timer) {
    case 0: config |= TIMER_SEL0; break;
    case 1: config |= TIMER_SEL1; break;
    case 2: config |= TIMER_SEL2; break;
    default: return 1;
  }

  sys_outb(TIMER_CTRL, config);

  switch (timer) {
    case 0: sys_outb(TIMER_0, LSB); sys_outb(TIMER_0, MSB); break;
    case 1: sys_outb(TIMER_1, LSB); sys_outb(TIMER_1, MSB); break;
    case 2: sys_outb(TIMER_2, LSB); sys_outb(TIMER_2, MSB); break;
    default: return -1;
  }

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id_timer;
  return sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id_timer);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id_timer);
}

void (timer_int_handler)() {
  timer_counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  if (!(timer == 0 || timer == 1 || timer == 2)) return 1;

  if (st == NULL) return 1;

  uint8_t command = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

  if (sys_outb(TIMER_CTRL,command)) return 1;
  
  return util_sys_inb(0x40+timer,st);

}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  if (!(timer == 0 || timer == 1 || timer == 2)) return 1;

  if (st == 0) return 1;

  union timer_status_field_val val;

  switch (field) {
    case tsf_all:
      val.byte = st;
      return timer_print_config(timer, field, val);
    case tsf_initial:
      val.in_mode = ((st & (BIT(4) | BIT(5))) >> 4);
      return timer_print_config(timer, field, val);
    case tsf_mode:
      val.count_mode = ((st & (BIT(1) | BIT(2) | BIT(3))) >> 1);
      return timer_print_config(timer, field, val);
    case tsf_base:
      val.bcd = (st & BIT(0));
      return timer_print_config(timer, field, val);
  }


}


