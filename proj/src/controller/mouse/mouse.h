#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <lcom/lcf.h>
#include "../KBC/i8042.h"
#include "../KBC/KBC.h"

int (mouse_subscribe_int)(uint32_t *mouse_irq);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

int (enable_data_reporting)();

int (disable_data_reporting)();

int (parse_packet)(uint8_t byte_no, struct packet *pp);

#endif

