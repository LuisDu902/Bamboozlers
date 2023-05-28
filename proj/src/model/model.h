#ifndef _MODEL_H_
#define _MODEL_H_

/**
 * @file model.h
 * @brief Sprites creation and destruction functions.
 */


#include "sprite.h"

#include "xpm/game_over/exit.xpm"
#include "xpm/game_over/play_again.xpm"
#include "xpm/game_over/game_over.xpm"
#include "xpm/cursor.xpm"
#include "xpm/game/panda.xpm"
#include "xpm/game/background.xpm"
#include "xpm/game/block.xpm"
#include "xpm/game/plank.xpm"
#include "xpm/home.xpm"
#include "xpm/numbers.xpm"
#include "xpm/game/lava.xpm"
#include "xpm/game/map.xpm"
#include "xpm/game/bamboo.xpm"
#include "xpm/instructions_text.xpm"
#include "xpm/levels/level1.xpm"
#include "xpm/levels/level2.xpm"
#include "xpm/levels/level3.xpm"
#include "xpm/menu/instructions.xpm"
#include "xpm/menu/levels.xpm"
#include "xpm/menu/logo.xpm"

Sprite* levels;
Sprite* logo;
Sprite* instructions;
Sprite *level_one;
Sprite *level_two;
Sprite *level_three;

Sprite *instructions_text_1;
Sprite *instructions_text_2;
Sprite *instructions_text_3;
Sprite *instructions_text_4;
Sprite *instructions_text_5;
Sprite *instructions_text_6;

Sprite *home;
Sprite *background;
Sprite *little_block;
Sprite *big_block;
Sprite *little_plank;
Sprite** map_items;
Sprite *big_plank;
Sprite* lava;
Sprite* map;
Sprite *panda;
Sprite *bamboo;
Sprite *timer[4];

Sprite *game_over;
Sprite *play_again;
Sprite *game_exit;

Sprite* cursor;
/**
 * @brief Creates all sprites used in the game.
 *
 * This function calls individual sprite creation functions to create
 * sprites for the mouse, menu, game, instructions, game over, and level select screens.
 */
void create_sprites();
/**
 * @brief Destroys all sprites used in the game.
 *
 * This function calls individual sprite destruction functions to destroy
 * sprites created in the `create_sprites()` function. It also destroys the mouse cursor sprite.
 */
void destroy_sprites();
/**
 * @brief Creates the mouse cursor sprites.
 *
 * This function creates sprites for the mouse cursor in different states,
 * such as normal, hand, and dragging. The sprites are created using XPM pixel maps.
 */
void create_mouse_sprites();


/**
 * @brief Creates the menu screen sprites.
 *
 * This function initializes various sprites used in the menu screen.
 * The sprites are created using XPM pixel maps.
 */
void create_menu_sprites();
/**
 * @brief Destroys the menu screen sprites.
 *
 * This function destroys the sprites created in `create_menu_sprites()`.
 * It releases the memory used by the sprites.
 */
void destroy_menu_sprites();

/**
 * @brief Creates the level select screen sprites.
 *
 * This function initializes various sprites used in the level select screen.
 * The sprites are created using XPM pixel maps.
 */
void create_level_select_sprites();
/**
 * @brief Destroys the level select screen sprites.
 *
 * This function destroys the sprites created in `create_level_select_sprites()`.
 * It releases the memory used by the sprites.
 */
void destroy_level_select_sprites();



/**
 * @brief Creates the instruction screen sprites.
 *
 * This function initializes various sprites used in the instruction screen.
 * The sprites are created using XPM pixel maps.
 */
void create_instructions_sprites();

/**
 * @brief Destroys the instruction screen sprites.
 *
 * This function destroys the sprites created in `create_instructions_sprites()`.
 * It releases the memory used by the sprites.
 */
void destroy_instructions_sprites();

/**
 * @brief Creates the game over screen sprites.
 */
void create_game_over_sprites();
/**
 * @brief Destroys the game over screen sprites.
 */
void destroy_game_over_sprites();


/**
 * @brief Creates the game sprites.
 *
 * This function initializes various sprites used in the game.
 * The sprites are created using XPM pixel maps.
 */
void create_game_sprites();

/**
 * @brief Destroys the game sprites.
 *
 * This function destroys the sprites created in `create_game_sprites()`.
 * It releases the memory used by the sprites.
 */
void destroy_game_sprites();
#endif

