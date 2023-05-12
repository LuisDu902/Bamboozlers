#ifndef _MODEL_H_
#define _MODEL_H_

#include <lcom/lcf.h>

#include "menu.h"
#include "game.h"
#include "xpm/cursor.xpm"
#include "xpm/hand.xpm"
#include "xpm/dragging.xpm"


extern Sprite *mouse;

Sprite* cursor;

void create_sprites();
void destroy_sprites();
void create_mouse_sprites();

#endif
