#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <lcom/lcf.h>

vbe_mode_info_t mode_info;
uint8_t* frame_buffer;

int (set_graphic_mode)(uint16_t mode);

int (set_text_mode)();

int (map_vram)(uint16_t mode);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (vg_draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);

int (vg_clear)();

#endif
