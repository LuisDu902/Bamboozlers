#include <lcom/lcf.h>

#include <stdint.h>
#define LAB3
#ifdef LAB3
    uint32_t count =0;
#endif
int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t i;

  if (sys_inb(port,&i) != 0) return 1;

  *value = i & 0xFF;
    #ifdef  LAB3
      count++;
    #endif
  return 0;
}

