#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include "viewer.h"
#include "controller/timer/timer.h"
#include "controller/RTC/rtc.h"

extern Sprite* mouse;
extern Sprite* map;
extern Sprite* block;
extern Sprite* little_plank;
extern Sprite* big_plank;
extern Sprite* home;


int (draw_game_menu)();
int (draw_map)();
int (draw_timer)();
int (draw_date)();
#endif
