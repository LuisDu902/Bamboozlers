#include "model.h"

void create_sprites()
{
    create_mouse_sprites();
    create_menu_sprites();
    create_game_sprites();
    create_instructions_sprites();
    create_game_over_sprites();
    create_level_select_sprites();
}

void destroy_sprites()
{
    destroy_menu_sprites();
    destroy_game_sprites();
    destroy_instructions_sprites();
    destroy_game_over_sprites();
    destroy_level_select_sprites();
    destroy_sprite(cursor);
}

void create_mouse_sprites()
{
    xpm_map_t pixmaps[] = {(xpm_map_t)cursor_xpm, (xpm_map_t)hand_xpm, (xpm_map_t) dragging_xpm};
    cursor = create_sprite_xpm(pixmaps, 3, 300, 400);
}

void create_game_over_sprites()
{
    xpm_map_t game_over_pixmaps[] = {(xpm_map_t)game_over_xpm};
    xpm_map_t exit_pixmaps[] = {(xpm_map_t)exit_xpm,(xpm_map_t)exit_sel_xpm};
    xpm_map_t play_again_pixmaps[] = {(xpm_map_t)play_again_xpm,(xpm_map_t)play_again_sel_xpm};
    
    game_over = create_sprite_xpm(game_over_pixmaps, 1, 132, 170);
    play_again = create_sprite_xpm(play_again_pixmaps, 2, 100, 350);
    game_exit = create_sprite_xpm(exit_pixmaps, 2, 450, 350);
}

void destroy_game_over_sprites()
{
    
   
}


void create_game_sprites()
{
    xpm_map_t panda_pixmaps[] = {
        (xpm_map_t)panda1_xpm,
        (xpm_map_t)panda2_xpm,
        (xpm_map_t)panda3_xpm,
        (xpm_map_t)panda4_xpm,
        (xpm_map_t)panda5_xpm,
        (xpm_map_t)panda6_xpm,
        (xpm_map_t)panda7_xpm,
        (xpm_map_t)panda8_xpm,
    };
    xpm_map_t little_block_pixmaps[] = {(xpm_map_t)little_block_xpm};
    xpm_map_t big_block_pixmaps[] = {(xpm_map_t)big_block_xpm};
    xpm_map_t little_plank_pixmaps[] = {(xpm_map_t)little_plank_xpm, (xpm_map_t)little_plank_r1_xpm, (xpm_map_t)little_plank_r2_xpm, (xpm_map_t)little_plank_r3_xpm, (xpm_map_t)little_plank_r4_xpm, (xpm_map_t)little_plank_r5_xpm, (xpm_map_t)little_plank_r6_xpm, (xpm_map_t)little_plank_r7_xpm};
    xpm_map_t big_plank_pixmaps[] = {(xpm_map_t)big_plank_xpm, (xpm_map_t)big_plank_r1_xpm, (xpm_map_t)big_plank_r2_xpm, (xpm_map_t)big_plank_r3_xpm, (xpm_map_t)big_plank_r4_xpm, (xpm_map_t)big_plank_r5_xpm, (xpm_map_t)big_plank_r6_xpm, (xpm_map_t)big_plank_r7_xpm};
    
    xpm_map_t maps_pixmaps[] = {(xpm_map_t)grama_xpm, (xpm_map_t)rock_xpm, (xpm_map_t)sand_xpm};
    xpm_map_t background_pixmaps[] = {(xpm_map_t)background_xpm};
    xpm_map_t lava_pixmaps[] = {(xpm_map_t)lava_xpm, (xpm_map_t)lava2_xpm, (xpm_map_t)lava3_xpm};
   
    xpm_map_t home_pixmaps[] = {(xpm_map_t)home_xpm};
    xpm_map_t bamboo_pixmaps[] = {(xpm_map_t)bamboo_xpm};
    
    xpm_map_t timer_pixmaps[] = {(xpm_map_t)number_0_xpm, (xpm_map_t)number_1_xpm, (xpm_map_t)number_2_xpm, (xpm_map_t)number_3_xpm, (xpm_map_t)number_4_xpm, (xpm_map_t)number_5_xpm, (xpm_map_t)number_6_xpm, (xpm_map_t)number_7_xpm, (xpm_map_t)number_8_xpm, (xpm_map_t)number_9_xpm};


    background = create_sprite_xpm(background_pixmaps, 1, 25, 25);
    lava = create_sprite_xpm(lava_pixmaps, 3, 25, 25);
    map = create_sprite_xpm(maps_pixmaps, 3, 25, 25);

    home = create_sprite_xpm(home_pixmaps, 1, 680, 250);

    panda = create_sprite_xpm(panda_pixmaps, 8, 40, 100);
   
   
    little_block = create_sprite_xpm(little_block_pixmaps, 1, 360, 520);
    big_block = create_sprite_xpm(big_block_pixmaps, 1, 410, 510);

    little_plank = create_sprite_xpm(little_plank_pixmaps, 8, 480, 535);
    big_plank = create_sprite_xpm(big_plank_pixmaps, 8, 585, 535);
    bamboo = create_sprite_xpm(bamboo_pixmaps, 1, 360, 370);

    
    for (int i = 0; i < 4 ; i++){
        timer[i] = create_sprite_xpm(timer_pixmaps, 10, 40 + i*30, 525);
    }
  
}

void destroy_game_sprites()
{
    destroy_sprite(panda);
    destroy_sprite(home);
    destroy_sprite(little_block);
    destroy_sprite(big_block);
    destroy_sprite(little_plank);
    destroy_sprite(big_plank);
    destroy_sprite(bamboo);
    for (int i = 0; i < 4; i++)
        destroy_sprite(timer[i]);
}

void create_instructions_sprites()
{
    xpm_map_t instructions_text_1_pixmaps[] = {(xpm_map_t)instructions_text_1_xpm};
    xpm_map_t instructions_text_2_pixmaps[] = {(xpm_map_t)instructions_text_2_xpm};
    xpm_map_t instructions_text_3_pixmaps[] = {(xpm_map_t)instructions_text_3_xpm};
    xpm_map_t instructions_text_4_pixmaps[] = {(xpm_map_t)instructions_text_4_xpm};
    xpm_map_t instructions_text_5_pixmaps[] = {(xpm_map_t)instructions_text_5_xpm};
    xpm_map_t instructions_text_6_pixmaps[] = {(xpm_map_t)instructions_text_6_xpm};
    instructions_text_1 = create_sprite_xpm(instructions_text_1_pixmaps, 1, 115, 100);
    instructions_text_2 = create_sprite_xpm(instructions_text_2_pixmaps, 1, 143, 175);
    instructions_text_3 = create_sprite_xpm(instructions_text_3_pixmaps, 1, 90, 250);
    instructions_text_4 = create_sprite_xpm(instructions_text_4_pixmaps, 1, 50, 325);
    instructions_text_5 = create_sprite_xpm(instructions_text_5_pixmaps, 1, 47, 400);
    instructions_text_6 = create_sprite_xpm(instructions_text_6_pixmaps, 1, 212, 475);
}

void destroy_instructions_sprites()
{
    destroy_sprite(instructions_text_1);
    destroy_sprite(instructions_text_2);
    destroy_sprite(instructions_text_3);
    destroy_sprite(instructions_text_4);
    destroy_sprite(instructions_text_5);
    destroy_sprite(instructions_text_6);
   
}

void create_level_select_sprites()
{
    xpm_map_t level_one_pixmaps[] = {(xpm_map_t)level1_xpm, (xpm_map_t)level1_sel_xpm};
    xpm_map_t level_two_pixmaps[] = {(xpm_map_t)level2_deny_xpm, (xpm_map_t)level2_sel_xpm, (xpm_map_t)level2_xpm};
    xpm_map_t level_three_pixmaps[] = {(xpm_map_t)level3_deny_xpm, (xpm_map_t)level3_sel_xpm, (xpm_map_t)level3_xpm};

    level_one = create_sprite_xpm(level_one_pixmaps, 2, 237, 100);
    level_two = create_sprite_xpm(level_two_pixmaps, 3, 237, 250);
    level_three = create_sprite_xpm(level_three_pixmaps, 3, 237, 400);
}

void destroy_level_select_sprites()
{
    destroy_sprite(level_one);
    destroy_sprite(level_two);
    destroy_sprite(level_three);
}

void create_menu_sprites(){
    xpm_map_t instructions_pixmaps[] = {(xpm_map_t)instructions_xpm, (xpm_map_t)instructions_sel_xpm};
    xpm_map_t levels_pixmaps[] = {(xpm_map_t)levels_xpm, (xpm_map_t)level_sel_xpm};
    xpm_map_t logo_pixmaps[] = {(xpm_map_t)logo_xpm};


    instructions = create_sprite_xpm(instructions_pixmaps,2, 405,430);
    levels = create_sprite_xpm(levels_pixmaps, 2, 120, 430);
    logo = create_sprite_xpm(logo_pixmaps, 1, 150, 50);
}

void destroy_menu_sprites(){
    destroy_sprite(instructions);
}

