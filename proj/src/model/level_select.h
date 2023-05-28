#ifndef _LEVEL_SELECT_H_
#define _LEVEL_SELECT_H_

#include "sprite.h"
#include "xpm/levels/level1.xpm"
#include "xpm/levels/level2.xpm"
#include "xpm/levels/level3.xpm"

Sprite *level_one;
Sprite *level_two;
Sprite *level_three;

void create_level_select_sprites();
void destroy_level_select_sprites();

#endif
