#include <lcom/lcf.h>
#include "game.h"

void create_game_sprites(){
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm, 40, 40);
    map = create_sprite_xpm((xpm_map_t) map0_xpm, 0, 0);
}

void destroy_game_sprites(){
    destroy_sprite(mouse);
}

