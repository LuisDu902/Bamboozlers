#include "game_viewer.h"

int (draw_game_menu)()
{    
    if (draw_map() != 0) return 1;
    if (draw_sprite(home)) return 1;
    if (draw_sprite(mouse) != 0) return 1;
    if (draw_sprite(block) != 0) return 1;
    if (draw_sprite(little_plank) != 0) return 1;
    if (draw_sprite(big_plank) != 0) return 1;
    return 0;
}


int(draw_map)() {
    for (int i = 0; i < BORDER_WIDTH; i++) {
        if (vg_draw_hline(20, 20 + i, MAP_WIDTH, 0xFFFFFF)) return 1;
        if (vg_draw_hline(20, 480 + i, MAP_WIDTH, 0xFFFFFF)) return 1;
        if (vg_draw_vline(20 + i, 20, MAP_HEIGHT, 0xFFFFFF)) return 1;
        if (vg_draw_vline(775 + i, 20, MAP_HEIGHT, 0xFFFFFF)) return 1;
    }
    return 0;
}

