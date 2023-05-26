#include "menu_viewer.h"

extern uint16_t xRes, yRes;

int (draw_main_menu)()
{
    if (draw_sprite(logo) != 0) return vg_exit();
    if (draw_sprite(text_main_menu) != 0) return vg_exit();
    
    return 0;
}
