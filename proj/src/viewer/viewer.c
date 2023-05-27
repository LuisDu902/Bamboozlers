#include "viewer.h"

extern Menu_state menu_state;
extern Item_state item_state;

extern Sprite *item;

int(draw_sprite)(Sprite *sprite)
{
    uint32_t color;
    uint16_t width = sprite->width[sprite->i], height = sprite->height[sprite->i], x = sprite->x, y = sprite->y;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            color = sprite->pixmap_array[sprite->i][col + row * width];
            if (color == TRANSPARENT)
                continue;
            if (vg_draw_pixel(x + col, y + row, color) )
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
    case INSTRUCTIONS:
        draw_instructions_menu();
        break;
    case GAME:
        draw_game_menu();
        break;
    case GAME_OVER:
        draw_game_over_menu();
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
        if (select_item(menu_play)){
            cursor->i = 1;
            menu_play->i = 1;
        }
        else if (select_item(instructions)){
            cursor->i = 1;
            instructions->i = 1;
        }
        else
        {
            cursor->i = 0;
            instructions->i = 0;
            menu_play->i = 0;
        }
        return draw_sprite(cursor);
        break;
    case GAME:
        if (item_state == INIT)
        {
            if ((select_item(little_block) && !is_in_map(little_block)) || 
                (select_item(little_plank) && !is_in_map(little_plank)) || 
                (select_item(big_plank) && !is_in_map(big_plank)) 
            ){
                cursor->i = 1;
            }
            else{
                cursor->i = 0;
            }
        }
        else if (item_state == DRAG)
        {
            cursor->i = 2;
        }
        return draw_sprite(cursor);
    case LEVEL_SELECTION:
    case INSTRUCTIONS:
    cursor->i = 0;
    return draw_sprite(cursor);
        
    case GAME_OVER:
    case EXIT:
        return 0;
    }

    return 0;
}
