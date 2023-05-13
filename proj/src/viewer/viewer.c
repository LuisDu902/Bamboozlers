#include <lcom/lcf.h>
#include "viewer.h"

extern Menu_state menu_state;
extern state_t state;

extern Sprite *item;

int(draw_sprite)(Sprite *sprite)
{
    uint32_t color;
    uint16_t width = sprite->width[sprite->current_pixmap], height = sprite->height[sprite->current_pixmap], x = sprite->x, y = sprite->y;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            color = sprite->pixmap_array[sprite->current_pixmap][col + row * width];
            if (color == 0xFFFFFE)
                continue;
            if (vg_draw_pixel(x + col, y + row, color) != 0)
                return 1;
        }
    }

    return 0;
}

int(draw_menu)()
{
    switch (menu_state)
    {
    case MENU:
        draw_main_menu();
        break;
    case LEVEL_SELECTION:
        draw_game_menu();
        break;
    case GAME:
        draw_game_menu();
        break;
    case GAME_OVER:
        draw_game_menu();
        break;
    case EXIT:
        return 0;
    }
    return draw_cursor();
}

int(draw_cursor)()
{
    switch (menu_state)
    {
    case MENU:
        if (select_item(text_main_menu)){
            cursor->current_pixmap = 1;
            text_main_menu->current_pixmap = 1;
        }
        else
        {
            cursor->current_pixmap = 0;
            text_main_menu->current_pixmap = 0;
        }
        return draw_sprite(cursor);
        break;
    case GAME:
        if (state == INIT)
        {
            if ((select_item(block) && !is_in_map(block)) || 
                (select_item(little_plank) && !is_in_map(little_plank)) || 
                (select_item(big_plank) && !is_in_map(big_plank)) 
            ){
                cursor->current_pixmap = 1;
            }
            else{
                cursor->current_pixmap = 0;
            }
        }
        else if (state == DRAG)
        {
            cursor->current_pixmap = 2;
        }
        return draw_sprite(cursor);
    case LEVEL_SELECTION:

    case GAME_OVER:
    case EXIT:
        return 0;
    }

    return 0;
}
