#ifndef _GAME_OVER_STATE_H_
#define _GAME_OVER_STATE_H_

#include "controller/KBC/KBC.h"
#include "controller/mouse/mouse.h"
#include "controller/keyboard/keyboard.h"
#include "controller/video/graphics.h"
#include "viewer/viewer.h"
#include "state.h"

extern Sprite* cursor;

void update_keyboard_game_over();
void update_mouse_game_over();



#endif
