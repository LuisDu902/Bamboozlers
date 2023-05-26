#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <lcom/lcf.h>

int (keyboard_subscribe_int)(uint8_t *bit_no);
int(keyboard_unsubscribe_int)();
void (kbd_ih)();
int (enable_int)();
#endif
