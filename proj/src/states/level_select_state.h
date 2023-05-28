#ifndef _LEVEL_SELECT_STATE_H_
#define _LEVEL_SELECT_STATE_H_

#include "controller/KBC/KBC.h"
#include "controller/mouse/mouse.h"
#include "controller/keyboard/keyboard.h"
#include "controller/video/graphics.h"
#include "viewer/viewer.h"
#include "state.h"

extern Sprite* cursor;
/**
 * @brief Updates the menu state based on the keyboard input in the instructions menu.
 */
void update_keyboard_level();
/**
 * @brief Updates the menu state based on the mouse input in the instructions menu.
 */
void update_mouse_level();

typedef enum {
    LEVEL_ONE,
    LEVEL_TWO,
    LEVEL_THREE,
} Level_state;

#endif
