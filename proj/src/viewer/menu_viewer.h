#ifndef _MENU_VIEWER_H_
#define _MENU_VIEWER_H_

#include "viewer.h"

extern Sprite* menu_title;
extern Sprite* menu_play;
extern Sprite* instructions;
extern Sprite* cursor;

int (draw_main_menu)();

int (draw_menu_cursor)();
#endif
