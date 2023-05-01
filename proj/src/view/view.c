#include <lcom/lcf.h>
#include "view.h"

extern uint8_t *frame_buffer;
extern Sprite *mouse;

int (vg_draw_sprite)(Sprite *sprite)
{
    uint32_t color;
    int width = sprite->width;
    int height = sprite->height;
    int x = sprite->x;
    int y = sprite->y;

    
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            color = sprite->pixmap[col + row * width];
            if (color == 0xFFFFFE) continue;
            if (vg_draw_pixel(x + col, y + row, color) != 0) return 1;
        }
    }

    return 0;
}
