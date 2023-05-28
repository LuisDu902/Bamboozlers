#ifndef _VIEWER_H_
#define _VIEWER_H_

/**
 * @file viewer.h
 * @brief Header file containing function declarations for viewer functions.
 */

#include "controller/video/graphics.h"
#include "model/model.h"
#include "states/state.h"
#include "controller/timer/timer.h"
#include "controller/RTC/rtc.h"

extern Sprite* map;
extern Sprite* lava;
extern Sprite* map;
extern Sprite* background;
extern Sprite* little_block;
extern Sprite* big_block;
extern Sprite* little_plank;
extern Sprite* big_plank;
extern Sprite* home;
extern Sprite* bamboo;

extern Sprite* game_over;
extern Sprite* play_again;
extern Sprite* game_exit;

extern Sprite* instructions_text_1;
extern Sprite* instructions_text_2;
extern Sprite* instructions_text_3;
extern Sprite* instructions_text_4;
extern Sprite* instructions_text_5;
extern Sprite* instructions_text_6;

extern Sprite* level_one;
extern Sprite* level_two;
extern Sprite* level_three;

extern Sprite* levels;
extern Sprite* instructions;
extern Sprite* logo;
extern Sprite* cursor;


/**
 * @brief Draws a sprite on the screen.
 *
 * This function draws a sprite on the screen at the specified position. It iterates over the
 * sprite's pixmap array and draws each pixel on the screen using the specified color.
 *
 * @param sprite The sprite to be drawn.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_sprite)(Sprite *sprite);

/**
 * @brief Draws the current menu on the screen.
 *
 * This function draws the current menu on the screen based on the current menu state.
 * It calls the corresponding menu drawing functions based on the menu state.
 *
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_menu)();

/**
 * @brief Draws the cursor on the screen based on the current menu state.
 *
 * This function draws the cursor on the screen based on the current menu state.
 * It calls the corresponding cursor drawing functions based on the menu state.
 *
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_cursor)();

/**
 * @brief Draws the game over menu.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_game_over_menu)();
/**
 * @brief Draws the cursor in the game over menu and updates its position based on the selected item.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_game_over_cursor)();


/**
 * @brief Draws the instructions menu with the instruction texts.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_instructions_menu)();


/**
 * @brief Draws the level selection menu with the level options.
 *
 * This function draws the level selection menu on the screen. It displays the level options
 * for the user to choose from.
 *
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_level_select_menu)();
/**
 * @brief Draws the level cursor based on the selected level.
 *
 * This function draws the level cursor on the selected level option. It updates the cursor and
 * level sprites based on the current level state.
 *
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_level_cursor)();

/**
 * @brief Draws the main menu with the menu options.
 *
 * This function draws the main menu on the screen. It displays the logo and menu options
 * for the user to choose from.
 *
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_main_menu)();

/**
 * @brief Draws the menu cursor based on the selected menu option.
 *
 * This function draws the menu cursor on the selected menu option. It updates the cursor and
 * menu sprites based on the current selection.
 *
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_menu_cursor)();

/**
 * @brief Draws the game menu including the map, inventory, background, timer, home, and other sprites.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_game_menu)();
/**
 * @brief Draws the inventory containers.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_inventory)();
/**
 * @brief Draws a container at the specified position and with the given width.
 * @param x The x-coordinate of the container.
 * @param y The y-coordinate of the container.
 * @param width The width of the container.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_container)(uint16_t x, uint16_t y, uint16_t width);
/**
 * @brief Draws the map borders.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_map)();
/**
 * @brief Draws the timer in the game menu.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_timer)();
/**
 * @brief Draws the game cursor based on the item state.
 * @return 1 if the drawing is successful, 0 otherwise.
 */
int (draw_game_cursor)();


#endif
