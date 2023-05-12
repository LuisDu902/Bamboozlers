#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "controller/KBC/KBC.h"
#include "controller/mouse/mouse.h"
#include "controller/keyboard/keyboard.h"
#include "controller/video/graphics.h"
#include "viewer/viewer.h"
#include "state.h"

extern Sprite* cursor;
extern Sprite* map;

typedef enum {INIT, DRAG} state_t;

void update_keyboard_game();
void update_mouse_game();

bool select_item(Sprite* item);
bool is_in_map(Sprite* item);
bool collide(Sprite* s1, Sprite* s2);
#endif
