#include <lcom/lcf.h>
#include "viewer.h"

extern Menu_state menu_state;

int (draw_sprite)(Sprite *sprite)
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

int (draw_menu)(){
    switch (menu_state) {
        case MENU:
            return draw_main_menu();
        case LEVEL_SELECTION:
            return draw_game_menu();
        case GAME:
            return draw_game_menu();
        case GAME_OVER:
            return draw_game_menu();
        case EXIT:
            return 0;
    }   
    return 1;
}
