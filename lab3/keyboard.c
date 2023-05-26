#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"

int hook_id=KBD_IRQ;
int error=1;
int counter=0;
uint8_t stat,scancode,cmd;
void kbd_ih(){
  while(1){    
    util_sys_inb(STAT_REG,&stat);
    if(stat & OBF){
      error = util_sys_inb(0x60,&scancode);
      if (error ==1)return;
      error = stat & (PAR_ERR | TO_ERR);
      return;
    }
  }
    tickdelay(micros_to_ticks(DELAY_US));
}

int (keyboard_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  return sys_irqsetpolicy(KBD_IRQ,(IRQ_REENABLE | IRQ_EXCLUSIVE),&hook_id);
}

int (keyboard_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

int enable_int(){
  if(sys_outb(0x64,0x20)!=0) return 1 ;
  util_sys_inb(0x60,&cmd);
  cmd |= BIT(0);
  sys_outb(0x64,0x60);
  sys_outb(0x60,cmd);
  return 0;
}

