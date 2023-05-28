#include "menu_viewer.h"

extern uint16_t xRes, yRes;

int(draw_main_menu)()
{
    if (draw_sprite(menu_title))
        return vg_exit();
    if (draw_sprite(menu_play))
        return vg_exit();
    if (draw_sprite(instructions))
        return vg_exit();

    return 0;
}

int(draw_menu_cursor)()
{
    if (select_item(menu_play))
    {
        cursor->i = menu_play->i = 1;
    }
    else if (select_item(instructions))
    {
        cursor->i = instructions->i = 1;
    }
    else
    {
        cursor->i = instructions->i = menu_play->i = 0;
    }
    return draw_sprite(cursor);
}
