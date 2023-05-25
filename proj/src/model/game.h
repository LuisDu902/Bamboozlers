#ifndef _GAME_H_
#define _GAME_H_

#include "sprite.h"
#include "xpm/mouse.xpm"
#include "xpm/map0.xpm"
#include "xpm/little_plank.xpm"
#include "xpm/big_plank.xpm"
#include "xpm/block.xpm"
#include "xpm/home.xpm"

Sprite *home;
Sprite *block;
Sprite *little_plank;
Sprite *big_plank;
Sprite *mouse;
Sprite *map;

void create_game_sprites();
void destroy_game_sprites();

#endif
