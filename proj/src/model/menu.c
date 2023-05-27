#include "menu.h"

void create_menu_sprites(){
    xpm_map_t menu_title_pixmaps[] = {(xpm_map_t)menu_title_xpm};
    xpm_map_t menu_play_pixmaps[] = {(xpm_map_t)menu_play_xpm, (xpm_map_t)menu_play_selected_xpm};
    xpm_map_t instructions_pixmaps[] = {(xpm_map_t)instructions_xpm, (xpm_map_t)instructions_selected_xpm};
    menu_title = create_sprite_xpm(menu_title_pixmaps,1, 280,100);
    menu_play = create_sprite_xpm(menu_play_pixmaps,2, 289,200);
    instructions = create_sprite_xpm(instructions_pixmaps,2, 110,300);
}

void destroy_menu_sprites(){
    destroy_sprite(menu_title);
    destroy_sprite(menu_play);
    destroy_sprite(instructions);
}
