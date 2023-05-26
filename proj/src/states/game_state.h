#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "controller/game/map_controller.h"
#include "controller/game/item_controller.h"
#include "controller/game/panda_controller.h"
#include "viewer/viewer.h"
#include "state.h"

void update_keyboard_game();
void update_mouse_game();

void update_panda_state();
#endif
