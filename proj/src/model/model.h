#ifndef _MODEL_H_
#define _MODEL_H_

#include <lcom/lcf.h>

#include "menu.h"
#include "game.h"

extern Sprite *mouse;
extern Sprite *play_button;
extern Sprite *main_menu;

void create_sprites();
void destroy_sprites();

#endif
