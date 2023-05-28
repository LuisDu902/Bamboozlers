#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include "viewer.h"
#include "controller/timer/timer.h"

extern Sprite* map;
extern Sprite* lava;
extern Sprite* grama;
extern Sprite* background;
extern Sprite* little_block;
extern Sprite* big_block;
extern Sprite* little_plank;
extern Sprite* big_plank;
extern Sprite* home;
extern Sprite* bamboo;


int (draw_game_menu)();
int (draw_map)();
int (draw_inventory)();
int (draw_container)(uint16_t x, uint16_t y, uint16_t width);
int (draw_map)();
int (draw_timer)();
int (draw_game_cursor)();
#endif
