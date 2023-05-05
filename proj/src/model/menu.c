#include <lcom/lcf.h>
#include "menu.h"

void create_menu_sprites(){
    play_button = create_sprite_xpm((xpm_map_t) play_button_xpm, 300, 450);
    main_menu = create_sprite_xpm((xpm_map_t) menu_xpm, 0, 0);
}

void destroy_menu_sprites(){
    destroy_sprite(main_menu);
    destroy_sprite(play_button);
}
