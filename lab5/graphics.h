#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>


int (set_graphic_mode)(uint16_t submode);
int (set_frame_buffer)(uint16_t mode);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_pixel)(uint8_t x, uint8_t y,uint32_t color);
int (normalize_color)(uint32_t color, uint32_t *new_color);
uint32_t (direct_mode)(unsigned j, unsigned i, uint8_t step, uint32_t first);
uint32_t (indexed_mode)(uint16_t col, uint16_t row, uint8_t step, uint32_t first, uint8_t n);


