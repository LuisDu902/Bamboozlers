#include "menu_viewer.h"

extern uint16_t xRes, yRes;

int (draw_main_menu)()
{
    if (draw_sprite(menu_title) ) return vg_exit();
    if (draw_sprite(menu_play) ) return vg_exit();
    if (draw_sprite(instructions) ) return vg_exit();
    
    return 0;
}
