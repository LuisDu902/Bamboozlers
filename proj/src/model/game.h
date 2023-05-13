#ifndef _GAME_H_
#define _GAME_H_

#include <lcom/lcf.h>
#include "sprite.h"
#include "xpm/mouse.xpm"
#include "xpm/map0.xpm"
#include "xpm/little_plank/little_plank.xpm"
#include "xpm/little_plank/little_plank_r1.xpm"
#include "xpm/little_plank/little_plank_r2.xpm"
#include "xpm/little_plank/little_plank_r3.xpm"
#include "xpm/little_plank/little_plank_r4.xpm"
#include "xpm/little_plank/little_plank_r5.xpm"
#include "xpm/little_plank/little_plank_r6.xpm"
#include "xpm/little_plank/little_plank_r7.xpm"
#include "xpm/big_plank/big_plank.xpm"
#include "xpm/big_plank/big_plank_r1.xpm"
#include "xpm/big_plank/big_plank_r2.xpm"
#include "xpm/big_plank/big_plank_r3.xpm"
#include "xpm/big_plank/big_plank_r4.xpm"
#include "xpm/big_plank/big_plank_r5.xpm"
#include "xpm/big_plank/big_plank_r6.xpm"
#include "xpm/big_plank/big_plank_r7.xpm"
#include "xpm/block.xpm"

Sprite *mouse;
Sprite *block;
Sprite *little_plank;
Sprite *big_plank;
Sprite *mouse;
Sprite *map;

void create_game_sprites();
void destroy_game_sprites();

#endif
