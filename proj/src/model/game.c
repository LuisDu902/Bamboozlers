#include <lcom/lcf.h>
#include "game.h"

void create_game_sprites(){
    xpm_map_t mouse_pixmaps[] = {(xpm_map_t)mouse_xpm};
    xpm_map_t level_pixmaps[] = {(xpm_map_t)map0_xpm};
    mouse = create_sprite_xpm(mouse_pixmaps, 1, 40, 40);
    map = create_sprite_xpm(level_pixmaps,1, 0, 0);
}

void destroy_game_sprites(){
    destroy_sprite(mouse);
}

