#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <lcom/lcf.h>
#include "controller/video/graphics.h"

typedef struct {
    int x, y;
    int width, height;
    int xspeed, yspeed;
    int num_pixmaps;
    int current_pixmap;
    uint32_t **pixmap_array;
} Sprite; 

Sprite *create_sprite_xpm(xpm_map_t *sprites, int num_sprites, int x, int y);
void destroy_sprite(Sprite *sprite);

#endif
