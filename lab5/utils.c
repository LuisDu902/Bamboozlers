#include <lcom/lcf.h>

#include <stdint.h>
#include "utils.h"

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t i;

  if (sys_inb(port,&i) != 0) return 1;

  *value = i & 0xFF;
    #ifdef  LAB3
      count++;
    #endif
  return 0;
}

