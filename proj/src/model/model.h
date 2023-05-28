#ifndef _MODEL_H_
#define _MODEL_H_


#include "menu.h"
#include "game.h"
#include "instructions.h"
#include "game_over.h"
#include "xpm/cursor.xpm"

Sprite* cursor;

void create_sprites();
void destroy_sprites();
void create_mouse_sprites();

#endif
