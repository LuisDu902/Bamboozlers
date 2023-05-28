#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include "viewer.h"
#include "controller/timer/timer.h"
#include "controller/RTC/rtc.h"
#include "states/menu_state.h"
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
int (draw_map)();
int (draw_timer)();
#endif
