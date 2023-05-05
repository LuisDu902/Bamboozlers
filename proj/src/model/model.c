#include <lcom/lcf.h>
#include "model.h"

void create_sprites(){
    create_menu_sprites();
    create_game_sprites();
}

void destroy_sprites(){
    destroy_menu_sprites();
    destroy_game_sprites();
}
