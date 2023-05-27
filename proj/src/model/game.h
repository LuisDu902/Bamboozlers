#ifndef _GAME_H_
#define _GAME_H_

#include "sprite.h"
#include "xpm/panda.xpm"
#include "xpm/map0.xpm"
#include "xpm/little_plank.xpm"
#include "xpm/big_plank.xpm"
#include "xpm/dirt.xpm"
#include "xpm/background.xpm"
#include "xpm/little_block.xpm"
#include "xpm/big_block.xpm"
#include "xpm/home.xpm"
#include "xpm/numbers.xpm"
#include "xpm/lava.xpm"
#include "xpm/grama.xpm"
#include "xpm/bamboo.xpm"

Sprite *home;
Sprite *background;
//Sprite *dirt_block_end;
//Sprite *dirt_block_start;
Sprite *little_block;
Sprite *big_block;
Sprite *little_plank;
Sprite** map_items;
Sprite *big_plank;
Sprite* lava;
Sprite* grama;
Sprite *panda;
Sprite *map;
Sprite *bamboo;
Sprite *timer[4];
Sprite *rtc[4];

void create_game_sprites();
void destroy_game_sprites();

#endif
