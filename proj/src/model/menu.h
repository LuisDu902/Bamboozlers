#ifndef _MENU_H_
#define _MENU_H_

#include <lcom/lcf.h>
#include "sprite.h"
#include "xpm/menu.xpm"
#include "xpm/play_button.xpm"

Sprite* play_button;
Sprite* main_menu;

void create_menu_sprites();
void destroy_menu_sprites();

#endif
