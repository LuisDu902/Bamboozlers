#ifndef _GAME_H_
#define _GAME_H_

#include "sprite.h"
#include "xpm/panda.xpm"
#include "xpm/map0.xpm"
#include "xpm/little_plank.xpm"
#include "xpm/big_plank.xpm"
#include "xpm/block.xpm"
#include "xpm/home.xpm"
#include "xpm/numbers.xpm"

Sprite *home;
Sprite *block;
Sprite *little_plank;
Sprite** map_items;
Sprite *big_plank;
Sprite *panda;
Sprite *map;
Sprite *timer[4];


void create_game_sprites();
void destroy_game_sprites();

#endif
