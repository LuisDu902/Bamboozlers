#include <lcom/lcf.h>
#include "menu_viewer.h"

int (draw_main_menu)()
{
    //if (draw_sprite(main_menu) != 0) return vg_exit();
    if (draw_sprite(mouse) != 0) return vg_exit();
    return 0;
}
