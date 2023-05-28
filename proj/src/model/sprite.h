#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "controller/video/graphics.h"

typedef struct {
    int x, y;
    int *width, *height;
    int xspeed, yspeed;
    int num_pixmaps;
    int i;
    uint32_t **pixmap_array;
} Sprite; 

Sprite *create_sprite_xpm(xpm_map_t *sprites, int num_sprites, int x, int y);
void destroy_sprite(Sprite *sprite);
void setPos(Sprite* sprite, int x, int y);

#endif
