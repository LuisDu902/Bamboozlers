#ifndef _MENU_H_
#define _MENU_H_

#include "sprite.h"
#include "xpm/logo.xpm"
#include "xpm/text_main_menu.xpm"
#include "xpm/text_selected.xpm"

Sprite* logo;
Sprite* text_main_menu;

void create_menu_sprites();
void destroy_menu_sprites();

#endif
