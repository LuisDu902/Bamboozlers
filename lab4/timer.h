#ifndef _LCOM_TIMER_H_
#define _LCOM_TIMER_H_

#include "i8254.h"
#include "utils.h"

#include <lcom/lcf.h>

int (timer_subscribe_int)(uint8_t *bit_no);

int (timer_unsubscribe_int)();

void (timer_int_handler)();

#endif /* _LCOM_TIMER_H */
