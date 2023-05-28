#ifndef _INSTRUCTIONS_STATE_H_
#define _INSTRUCTIONS_STATE_H_

/**
 * @file menu_state.h
 * @brief Header file containing function declarations for menu state update functions.
 */

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
void (update_keyboard_instructions)();


#endif
