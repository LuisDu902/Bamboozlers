#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <lcom/lcf.h>
#include "controllers/video/graphics.h"

typedef struct {
    int x, y;
    int width, height;
    int xspeed, yspeed;
    uint32_t *pixmap;
} Sprite; 

Sprite *create_sprite_xpm(xpm_map_t sprite, int x, int y);
void destroy_sprite(Sprite *sprite);

#endif
