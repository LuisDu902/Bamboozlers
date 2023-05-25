#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "controller/KBC/KBC.h"
#include "controller/mouse/mouse.h"
#include "controller/keyboard/keyboard.h"
#include "controller/video/graphics.h"
#include "viewer/viewer.h"
#include "state.h"
#include "model/config.h"


void update_keyboard_game();
void update_mouse_game();

bool is_in_map(Sprite* item);
bool collide(Sprite* s1, Sprite* s2);

void update_hero_pos();

#endif
