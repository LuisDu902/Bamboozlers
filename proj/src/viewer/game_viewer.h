#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include "viewer.h"

extern Sprite* mouse;
extern Sprite* map;
extern Sprite* block;
extern Sprite* little_plank;
extern Sprite* big_plank;
extern Sprite* home;

int (draw_game_menu)();
int (draw_map)();

#endif
