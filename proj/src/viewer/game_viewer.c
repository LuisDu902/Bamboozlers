#include <lcom/lcf.h>
#include "game_viewer.h"

int (draw_game_menu)()
{
    if (draw_sprite(map) != 0) return 1;
    if (draw_sprite(mouse) != 0) return 1;
    return 0;
}
