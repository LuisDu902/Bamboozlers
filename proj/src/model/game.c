#include <lcom/lcf.h>
#include "game.h"

void create_game_sprites(){
    
    xpm_map_t mouse_pixmaps[] = {(xpm_map_t)mouse_xpm};
    xpm_map_t block_pixmaps[] = {(xpm_map_t)block_xpm};
    xpm_map_t level_pixmaps[] = {(xpm_map_t)map0_xpm};
    xpm_map_t little_plank_pixmaps[] = {(xpm_map_t) little_plank_xpm};
    xpm_map_t big_plank_pixmaps[] = {(xpm_map_t) big_plank_xpm};

    mouse = create_sprite_xpm(mouse_pixmaps, 1, 40, 40);
    map = create_sprite_xpm(level_pixmaps,1, 0, 0);
    block = create_sprite_xpm(block_pixmaps,1, 470, 400);
    little_plank = create_sprite_xpm(little_plank_pixmaps,1, 500, 405);
    big_plank = create_sprite_xpm(big_plank_pixmaps,1, 600, 405);
}

void destroy_game_sprites(){
    destroy_sprite(mouse);
    destroy_sprite(map);
    destroy_sprite(block);
    destroy_sprite(little_plank);
    destroy_sprite(big_plank);
}

