#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include <lcom/lcf.h>
#include "viewer.h"

extern Sprite* mouse;
extern Sprite* map;
vbe_mode_info_t mode_info;

int (draw_game_menu)();

#endif
