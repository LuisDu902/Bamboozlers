#ifndef _GAME_H_
#define _GAME_H_

#include "sprite.h"
#include "xpm/game/panda.xpm"
#include "xpm/game/background.xpm"
#include "xpm/game/block.xpm"
#include "xpm/game/plank.xpm"
#include "xpm/home.xpm"
#include "xpm/numbers.xpm"
#include "xpm/game/lava.xpm"
#include "xpm/game/grama.xpm"
#include "xpm/game/bamboo.xpm"

Sprite *home;
Sprite *background;
Sprite *little_block;
Sprite *big_block;
Sprite *little_plank;
Sprite** map_items;
Sprite *big_plank;
Sprite* lava;
Sprite* grama;
Sprite *panda;
Sprite *bamboo;
Sprite *timer[4];


void create_game_sprites();
void destroy_game_sprites();

#endif
