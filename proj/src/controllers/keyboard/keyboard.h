#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <lcom/lcf.h>
#include "../KBC/i8042.h"
#include "../KBC/KBC.h"

int (keyboard_subscribe_int)(uint32_t *keyboard_irq);

int (keyboard_unsubscribe_int)();

int (read_scancode)();

int (enable_keyboard_int)();

#endif
