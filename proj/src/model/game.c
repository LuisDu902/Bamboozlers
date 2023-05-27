#include "game.h"

void create_game_sprites()
{
    xpm_map_t panda_pixmaps[] = {
        (xpm_map_t)panda_right_1_xpm,
        (xpm_map_t)panda_right_2_xpm,
        (xpm_map_t)panda_right_3_xpm,
        (xpm_map_t)panda_left_1_xpm,
        (xpm_map_t)panda_left_2_xpm,
        (xpm_map_t)panda_left_3_xpm,
        (xpm_map_t)panda_right_jump_xpm,
        (xpm_map_t)panda_left_jump_xpm,
    };
    xpm_map_t little_block_pixmaps[] = {(xpm_map_t)little_block_xpm};
    xpm_map_t big_block_pixmaps[] = {(xpm_map_t)big_block_xpm};
    xpm_map_t little_plank_pixmaps[] = {(xpm_map_t)little_plank_xpm, (xpm_map_t)little_plank_r1_xpm, (xpm_map_t)little_plank_r2_xpm, (xpm_map_t)little_plank_r3_xpm, (xpm_map_t)little_plank_r4_xpm, (xpm_map_t)little_plank_r5_xpm, (xpm_map_t)little_plank_r6_xpm, (xpm_map_t)little_plank_r7_xpm};
    xpm_map_t big_plank_pixmaps[] = {(xpm_map_t)big_plank_xpm, (xpm_map_t)big_plank_r1_xpm, (xpm_map_t)big_plank_r2_xpm, (xpm_map_t)big_plank_r3_xpm, (xpm_map_t)big_plank_r4_xpm, (xpm_map_t)big_plank_r5_xpm, (xpm_map_t)big_plank_r6_xpm, (xpm_map_t)big_plank_r7_xpm};
    

    xpm_map_t grama_pixmaps[] = {(xpm_map_t)grama_xpm};
    xpm_map_t background_pixmaps[] = {(xpm_map_t)background_xpm};
    xpm_map_t lava_pixmaps[] = {(xpm_map_t)lava_xpm};
   
   // xpm_map_t dirt_block_pixmaps[] = {(xpm_map_t)dirt_xpm};
    
    xpm_map_t level_pixmaps[] = {(xpm_map_t)map0_xpm};
    xpm_map_t home_pixmaps[] = {(xpm_map_t)home_xpm};
    xpm_map_t bamboo_pixmaps[] = {(xpm_map_t)bamboo_xpm};
    
    xpm_map_t timer_pixmaps[] = {(xpm_map_t)number_0_xpm, (xpm_map_t)number_1_xpm, (xpm_map_t)number_2_xpm, (xpm_map_t)number_3_xpm, (xpm_map_t)number_4_xpm, (xpm_map_t)number_5_xpm, (xpm_map_t)number_6_xpm, (xpm_map_t)number_7_xpm, (xpm_map_t)number_8_xpm, (xpm_map_t)number_9_xpm};


    background = create_sprite_xpm(background_pixmaps, 1, 25, 25);
    lava = create_sprite_xpm(lava_pixmaps, 1, 25, 25);
    grama = create_sprite_xpm(grama_pixmaps, 1, 25, 25);


    home = create_sprite_xpm(home_pixmaps, 1, 500, 30);

    panda = create_sprite_xpm(panda_pixmaps, 8, 25, 100);
   
    map = create_sprite_xpm(level_pixmaps, 1, 0, 0);
   
    
    //dirt_block_end = create_sprite_xpm(dirt_block_pixmaps, 1,340 ,150 );
    //dirt_block_start = create_sprite_xpm(dirt_block_pixmaps, 1, 25,420 );
    little_block = create_sprite_xpm(little_block_pixmaps, 1, 400, 500);
    big_block = create_sprite_xpm(big_block_pixmaps, 1, 470, 500);

    little_plank = create_sprite_xpm(little_plank_pixmaps, 8, 500, 505);
    bamboo = create_sprite_xpm(bamboo_pixmaps, 1, 350, 120);

    big_plank = create_sprite_xpm(big_plank_pixmaps, 8, 600, 505);
    timer[0]=create_sprite_xpm(timer_pixmaps,10,100,505);
    timer[1]=create_sprite_xpm(timer_pixmaps,10,130,505);
    timer[2]=create_sprite_xpm(timer_pixmaps,10,160,505);
    timer[3]=create_sprite_xpm(timer_pixmaps,10,190,505);
    rtc[0]=create_sprite_xpm(timer_pixmaps,10,400,105);
    rtc[1]=create_sprite_xpm(timer_pixmaps,10,430,105);
    rtc[2]=create_sprite_xpm(timer_pixmaps,10,460,105);
    rtc[3]=create_sprite_xpm(timer_pixmaps,10,490,105);

}

void destroy_game_sprites()
{
    destroy_sprite(panda);
    destroy_sprite(home);
    destroy_sprite(map);
    destroy_sprite(little_block);
    destroy_sprite(big_block);
    destroy_sprite(little_plank);
    destroy_sprite(big_plank);
    destroy_sprite(bamboo);
    for (int i = 0; i < 4; i++){
        destroy_sprite(timer[i]);
        destroy_sprite(rtc[i]);
    }
    
}
