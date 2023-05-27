#ifndef _STATE_H_
#define _STATE_H_

#include "menu_state.h"
#include "game_state.h"
#include "controller/RTC/rtc.h"
#include "instructions_state.h"

typedef enum {
    MENU,
    LEVEL_SELECTION,
    INSTRUCTIONS, 
    GAME,
    GAME_OVER,
    EXIT
} Menu_state;

void update_keyboard_state();
void update_mouse_state();
void update_timer_state();
void update_rtc_state();
void update_cursor_position();

bool select_item(Sprite* item);

#endif
