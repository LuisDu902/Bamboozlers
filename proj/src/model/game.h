#ifndef _GAME_H_
#define _GAME_H_

#include <lcom/lcf.h>
#include "sprite.h"
#include "xpm/mouse.xpm"
#include "xpm/map0.xpm"

Sprite *mouse;
Sprite *map;

void create_game_sprites();
void destroy_game_sprites();

#endif
