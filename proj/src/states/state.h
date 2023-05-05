#ifndef _STATE_H_
#define _STATE_H_

#include "menu_state.h"
#include "game_state.h"

typedef enum {
    MENU,
    LEVEL_SELECTION, 
    GAME,
    GAME_OVER,
    EXIT
} Menu_state;

typedef enum {
    CHILLING, 
    RUNNING,
    JUMPING,
    WALL_CLIMBING,
    CARRYING,
    DYING
} Game_state;

void update_keyboard_state();

#endif
