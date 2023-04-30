#include <lcom/lcf.h>

#include <stdint.h>

#include "keyboard.h"

int keyboard_hook_id = 1;
uint8_t scancode;

int (keyboard_subscribe_int)(uint32_t *keyboard_irq) {
  *keyboard_irq = BIT(keyboard_hook_id);
  return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id);
}

int (keyboard_unsubscribe_int)() {
  return sys_irqrmpolicy(&keyboard_hook_id);
}

int (read_scancode)(){
    return read_output(KBC_OUT_BUF, &scancode, true);
}

int (enable_keyboard_int)(){
  
    uint8_t config;

    if (write_command(KBC_IN_BUF, KBC_READ_CMD) != 0) return 1;
    if (read_output(KBC_OUT_BUF, &config, true) != 0) return 1;
   
    config |= KBC_INT;

    if (write_command(KBC_IN_BUF, KBC_WRITE_CMD) != 0) return 1;
    if (write_command(KBC_OUT_BUF, config) != 0) return 1;

    return 0;
}
