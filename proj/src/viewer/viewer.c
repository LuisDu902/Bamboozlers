#include <lcom/lcf.h>
#include "viewer.h"

extern Menu_state menu_state;

int(draw_sprite)(Sprite *sprite)
{
    uint32_t color;
    uint16_t width = sprite->width, height = sprite->height, x = sprite->x, y = sprite->y;

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
        if (cursor->x >= mouse->x && cursor->x <= mouse->x + mouse->width &&
            cursor->y >= mouse->y && cursor->y <= mouse->y + mouse->width)
            cursor->current_pixmap = 1;
        else{
            cursor->current_pixmap = 0;
        }
        return draw_sprite(cursor);
        break;
    case GAME:
        cursor->current_pixmap = 0;
        return draw_sprite(cursor);
    case LEVEL_SELECTION:
    
    case GAME_OVER:
    case EXIT:
        return 0;
    }

    return 0;
}
