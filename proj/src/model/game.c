#include "game.h"

void create_game_sprites()
{

   xpm_map_t panda_pixmaps[] = {
        (xpm_map_t)panda_right_1_xpm,
        (xpm_map_t)panda_right_3_xpm,
        (xpm_map_t)panda_right_4_xpm,
        (xpm_map_t)panda_left_1_xpm,
        (xpm_map_t)panda_left_3_xpm,
        (xpm_map_t)panda_left_4_xpm,
        (xpm_map_t)panda_left_jump_xpm,
    };
    xpm_map_t block_pixmaps[] = {(xpm_map_t)block_xpm};
    xpm_map_t level_pixmaps[] = {(xpm_map_t)map0_xpm};
<<<<<<< HEAD
    xpm_map_t little_plank_pixmaps[] = {(xpm_map_t) little_plank_xpm, (xpm_map_t) little_plank_r1_xpm, (xpm_map_t) little_plank_r2_xpm, (xpm_map_t) little_plank_r3_xpm, (xpm_map_t) little_plank_r4_xpm, (xpm_map_t) little_plank_r5_xpm, (xpm_map_t) little_plank_r6_xpm, (xpm_map_t) little_plank_r7_xpm};
    xpm_map_t big_plank_pixmaps[] = {(xpm_map_t) big_plank_xpm, (xpm_map_t) big_plank_r1_xpm, (xpm_map_t) big_plank_r2_xpm, (xpm_map_t) big_plank_r3_xpm, (xpm_map_t) big_plank_r4_xpm, (xpm_map_t) big_plank_r5_xpm, (xpm_map_t) big_plank_r6_xpm, (xpm_map_t) big_plank_r7_xpm};
    xpm_map_t home_pixmaps[] = {(xpm_map_t) home_xpm};
    xpm_map_t timer_pixmaps[]= {(xpm_map_t) number_0_xpm, (xpm_map_t) number_1_xpm, (xpm_map_t) number_2_xpm, (xpm_map_t) number_3_xpm, (xpm_map_t) number_4_xpm, (xpm_map_t) number_5_xpm, (xpm_map_t) number_6_xpm, (xpm_map_t) number_7_xpm, (xpm_map_t) number_8_xpm ,(xpm_map_t) number_9_xpm};
=======
    xpm_map_t little_plank_pixmaps[] = {(xpm_map_t)little_plank_xpm, (xpm_map_t)little_plank_r1_xpm, (xpm_map_t)little_plank_r2_xpm, (xpm_map_t)little_plank_r3_xpm, (xpm_map_t)little_plank_r4_xpm, (xpm_map_t)little_plank_r5_xpm, (xpm_map_t)little_plank_r6_xpm, (xpm_map_t)little_plank_r7_xpm};
    xpm_map_t big_plank_pixmaps[] = {(xpm_map_t)big_plank_xpm, (xpm_map_t)big_plank_r1_xpm, (xpm_map_t)big_plank_r2_xpm, (xpm_map_t)big_plank_r3_xpm, (xpm_map_t)big_plank_r4_xpm, (xpm_map_t)big_plank_r5_xpm, (xpm_map_t)big_plank_r6_xpm, (xpm_map_t)big_plank_r7_xpm};
    xpm_map_t home_pixmaps[] = {(xpm_map_t)home_xpm};
>>>>>>> 4fc26bc (refactoring)

    home = create_sprite_xpm(home_pixmaps, 1, 500, 30);
  
    panda = create_sprite_xpm(panda_pixmaps, 7, 50, 396);

    map = create_sprite_xpm(level_pixmaps, 1, 0, 0);
    block = create_sprite_xpm(block_pixmaps, 1, 470, 500);
    little_plank = create_sprite_xpm(little_plank_pixmaps, 8, 500, 505);
    big_plank = create_sprite_xpm(big_plank_pixmaps, 8, 600, 505);
<<<<<<< HEAD
    timer[0]=create_sprite_xpm(timer_pixmaps,10,100,505);
    timer[1]=create_sprite_xpm(timer_pixmaps,10,130,505);
    timer[2]=create_sprite_xpm(timer_pixmaps,10,160,505);
    timer[3]=create_sprite_xpm(timer_pixmaps,10,190,505);
=======
    map_items = (Sprite **)malloc(50 * sizeof(Sprite *));
>>>>>>> 4fc26bc (refactoring)
}

void destroy_game_sprites()
{
    destroy_sprite(panda);
    destroy_sprite(home);
    destroy_sprite(map);
    destroy_sprite(block);
    destroy_sprite(little_plank);
    destroy_sprite(big_plank);
    for(int i=0;i<4;i++)
        destroy_sprite(timer[i]);
}
