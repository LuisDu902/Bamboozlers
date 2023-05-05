#ifndef _KBC_H_
#define _KBC_H_

#include <lcom/lcf.h>
#include "i8042.h"

int (get_KBC_status)(uint8_t *status);

int (check_KBC_status)(uint8_t status);

int (write_command)(int port, uint8_t command);

int (read_output)(int port, uint8_t *output, bool keyboard);

#endif
