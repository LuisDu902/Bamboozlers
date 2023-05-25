#include "game.h"

void create_game_sprites(){
    
    xpm_map_t mouse_pixmaps[] = {(xpm_map_t)mouse_xpm};
    xpm_map_t block_pixmaps[] = {(xpm_map_t)block_xpm};
    xpm_map_t level_pixmaps[] = {(xpm_map_t)map0_xpm};
    xpm_map_t little_plank_pixmaps[] = {(xpm_map_t) little_plank_xpm, (xpm_map_t) little_plank_r1_xpm, (xpm_map_t) little_plank_r2_xpm, (xpm_map_t) little_plank_r3_xpm, (xpm_map_t) little_plank_r4_xpm, (xpm_map_t) little_plank_r5_xpm, (xpm_map_t) little_plank_r6_xpm, (xpm_map_t) little_plank_r7_xpm};
    xpm_map_t big_plank_pixmaps[] = {(xpm_map_t) big_plank_xpm, (xpm_map_t) big_plank_r1_xpm, (xpm_map_t) big_plank_r2_xpm, (xpm_map_t) big_plank_r3_xpm, (xpm_map_t) big_plank_r4_xpm, (xpm_map_t) big_plank_r5_xpm, (xpm_map_t) big_plank_r6_xpm, (xpm_map_t) big_plank_r7_xpm};
    xpm_map_t home_pixmaps[] = {(xpm_map_t) home_xpm};

    home = create_sprite_xpm(home_pixmaps, 1, 500, 30);
    mouse = create_sprite_xpm(mouse_pixmaps, 1, 50, 410);
    map = create_sprite_xpm(level_pixmaps, 1, 0, 0);
    block = create_sprite_xpm(block_pixmaps, 1, 470, 500);
    little_plank = create_sprite_xpm(little_plank_pixmaps, 8, 500, 505);
    big_plank = create_sprite_xpm(big_plank_pixmaps, 8, 600, 505);
}

void destroy_game_sprites(){
    destroy_sprite(home);
    destroy_sprite(mouse);
    destroy_sprite(map);
    destroy_sprite(block);
    destroy_sprite(little_plank);
    destroy_sprite(big_plank);
}

