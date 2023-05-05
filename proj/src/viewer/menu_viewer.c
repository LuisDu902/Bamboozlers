#include <lcom/lcf.h>
#include "menu_viewer.h"

int (draw_main_menu)()
{
    if (draw_sprite(main_menu) != 0) return 1;
   // if (draw_sprite(play_button) != 0) return 1;
    return 0;
}
