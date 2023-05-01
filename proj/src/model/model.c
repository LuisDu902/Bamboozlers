#include <lcom/lcf.h>
#include "model.h"

Sprite *mouse;

void create_sprites(){
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm, 40, 40);
}

void destroy_sprites(){
    destroy_sprite(mouse);
}
