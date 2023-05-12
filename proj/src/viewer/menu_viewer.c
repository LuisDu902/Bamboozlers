#include <lcom/lcf.h>
#include "menu_viewer.h"

extern uint16_t xRes, yRes;

int (draw_main_menu)()
{
    //if(vg_draw_rectangle(0,0,xRes,yRes,0x114050)!=0)return vg_exit();
    if (draw_sprite(logo) != 0) return vg_exit();
    if (draw_sprite(text_main_menu) != 0) return vg_exit();
    
    return 0;
}
