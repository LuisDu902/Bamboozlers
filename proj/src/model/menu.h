#ifndef _MENU_H_
#define _MENU_H_

#include "sprite.h"
#include "xpm/menu_title.xpm"
#include "xpm/menu_play.xpm"
#include "xpm/instructions.xpm"


Sprite* menu_title;
Sprite* menu_play;
Sprite* instructions;

void create_menu_sprites();
void destroy_menu_sprites();

#endif
