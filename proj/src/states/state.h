#ifndef _STATE_H_
#define _STATE_H_

/**
 * @file state.h
 * @brief Header file containing function declarations for state update functions.
 */

#include "controller/KBC/KBC.h"
#include "controller/mouse/mouse.h"
#include "controller/keyboard/keyboard.h"
#include "controller/game/controller.h"
#include "controller/video/graphics.h"
#include "controller/RTC/rtc.h"
#include "viewer/viewer.h"
#include "model/config.h"

extern Sprite* cursor;

/**
 * @brief Updates the state based on the keyboard input.
 */
void update_keyboard_state();
/**
 * @brief Updates the state based on the mouse input.
 */
void update_mouse_state();
/**
 * @brief Updates the state based on the timer interrupt.
 */
void update_timer_state();
/**
 * @brief Updates the cursor position based on the mouse input.
 */
void update_cursor_position();

/**
 * @brief Updates the keyboard input in the game over state.
 * 
 * Reads the current scancode and updates the menu state based on the pressed key.
 */
void update_keyboard_game_over();
/**
 * @brief Updates the mouse input in the game over state.
 * 
 * Checks the mouse button status and updates the menu state based on the clicked item.
 */
void update_mouse_game_over();

/**
 * @brief Updates the menu state based on the keyboard input in the instructions menu.
 */
void update_keyboard_instructions();


/**
 * @brief Updates the menu state based on the keyboard input in the main menu.
 */
void update_keyboard_menu();

/**
 * @brief Updates the menu state based on the mouse input in the main menu.
 */
void update_mouse_menu();

/**
 * @brief Updates the menu state based on the keyboard input in the instructions menu.
 */
void update_keyboard_level();
/**
 * @brief Updates the menu state based on the mouse input in the instructions menu.
 */
void update_mouse_level();

/**
 * @brief Updates the game state based on the keyboard input.
 */
void update_keyboard_game();
/**
 * @brief Updates the game state based on the mouse input.
 */
void update_mouse_game();
/**
 * @brief Updates the game state based on the timer interrupt.
 */
void update_timer_game();
/**
 * @brief Updates the state of the panda character.
 */
void update_panda_state();

#endif
