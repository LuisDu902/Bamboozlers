#include <lcom/lcf.h>
#include "menu.h"

void create_menu_sprites(){
    xpm_map_t logo_pixmaps[] = {(xpm_map_t)logo_xpm};
    xpm_map_t text_main_menu_pixmaps[] = {(xpm_map_t)text_main_menu_xpm, (xpm_map_t)text_selected_xpm};
    logo = create_sprite_xpm(logo_pixmaps,1, 50,10+100);
    text_main_menu = create_sprite_xpm(text_main_menu_pixmaps,2, 50,358+100);
}

void destroy_menu_sprites(){
    destroy_sprite(logo);
    destroy_sprite(text_main_menu);
}
