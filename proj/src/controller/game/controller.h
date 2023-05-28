#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "../KBC/KBC.h"
#include "../mouse/mouse.h"
#include "../timer/timer.h"
#include "../keyboard/keyboard.h"
#include "../video/graphics.h"
#include "model/sprite.h"
#include "model/config.h"
#include "states/state.h"

extern Sprite* panda;
extern Sprite* item;
extern Sprite* map;
extern Sprite* home;
extern Sprite* lava;
extern Sprite* bamboo;
extern Sprite* little_block;
extern Sprite* little_plank;
extern Sprite* big_block;
extern Sprite* big_plank;
extern uint8_t scancode;

Sprite* item;
Sprite* collide_item;

int16_t item_x, item_y, off_x, off_y;

int minutes;
int seconds;

extern int counter;
extern Panda_state panda_state;
extern bool isRightPressed;
extern bool isLeftPressed;

/**
 * @brief Checks if an item is within the map boundaries.
 *
 * This function checks if the specified item is within the boundaries of the map.
 *
 * @param item The item to check.
 * @return True if the item is within the map boundaries, false otherwise.
 */
bool is_in_map(Sprite* item);

/**
 * @brief Checks if two sprites collide.
 *
 * This function checks if two sprites collide by comparing their bounding boxes pixel by pixel.
 *
 * @param s1 The first sprite.
 * @param s2 The second sprite.
 * @return True if the sprites collide, false otherwise.
 */
bool collide(Sprite* s1, Sprite* s2);

/**
 * @brief Sets up the game map for a specific level.
 *
 * This function sets up the game map based on the specified level.
 * It positions the sprites (panda, home, little_block, big_block, little_plank, big_plank, bamboo) according to the level.
 *
 * @param level The level of the game.
 */
void map_set_up(int level);


/* ------------------------------------------------------------------------------ */
/* -------------------------------PANDA CONTROLLER------------------------------- */
/* ------------------------------------------------------------------------------ */


/**
 * @brief Checks if the panda is above a given item.
 *
 * This function checks if the panda is positioned above the specified item.
 *
 * @param item The item to check.
 * @return True if the panda is above the item, false otherwise.
 */
bool above(Sprite* item);

/**
 * @brief Moves the panda character to the left.
 *
 * This function moves the panda character to the left.
 */
void move_left();

/**
 * @brief Moves the panda character to the left.
 *
 * This function moves the panda character to the right.
 */
void move_right();


/**
 * @brief Makes the panda character jump.
 *
 * This function makes the panda character jump by adjusting its position based on the specified time and height.
 *
 * @param time The time elapsed since the jump started.
 * @param y The initial y-coordinate of the jump.
 */
void jump(uint32_t time, uint32_t y);

/**
 * @brief Makes the panda character fall.
 *
 * This function makes the panda character fall by adjusting its position based on the specified time and height.
 *
 * @param time The time elapsed since the fall started.
 * @param y The initial y-coordinate of the fall.
 */
void fall(uint32_t time, uint32_t y);

/**
 * @brief Checks if the panda hits the floor.
 *
 * This function checks if the panda hits the floor (the bottom boundary of the map).
 *
 * @return True if the panda hits the floor, false otherwise.
 */
bool hit_floor();
/**
 * @brief Handles the boundary conditions for the panda character.
 *
 * This function handles the boundary conditions for the panda character, ensuring it stays within the map boundaries.
 */
void handle_boundary_conditions();
/**
 * @brief Checks if the panda collides with any items.
 *
 * This function checks if the panda collides with any items on the map, such as little_block, little_plank, big_plank, big_block, or map.
 * If a collision is detected, the collide_item variable is set to the collided item.
 *
 * @return True if the panda collides with an item, false otherwise.
 */
bool collide_with_items();
/**
 * @brief Checks if the panda is above any item.
 *
 * This function checks if the panda is positioned above any item on the map.
 *
 * @return True if the panda is above an item, false otherwise.
 */
bool above_any_item();
/**
 * @brief Fixes the collision between the panda and the collided item.
 *
 * This function fixes the collision between the panda and the collided item by adjusting the panda's position.
 * If the collision is on the right side of the item, the panda moves to the left; if the collision is on the left side, the panda moves to the right.
 */
void fix_collision();
/**
 * @brief Fixes the collision between the panda and the collided item during a jump.
 *
 * This function fixes the collision between the panda and the collided item during a jump by adjusting the panda's position.
 */
void fix_jump_collision();
/**
 * @brief Fixes the collision between the panda and the collided item during a fall.
 *
 * This function fixes the collision between the panda and the collided item during a fall by adjusting the panda's position.
 */
void fix_fall_collision();

/**
 * @brief Updates the panda character's animation frame.
 *
 * This function updates the panda character's animation frame based on its current state (JUMP or RUN) and movement direction (left or right).
 */
void update_panda_animation();

/**
 * @brief Checks if an item is selected and updates the item's position.
 *
 * This function checks if any item is selected by the player and if the selected item is not already on the game map.
 * If a valid item is selected, its position is updated based on the cursor position.
 *
 * @return True if an item is selected and updated successfully, False otherwise.
 */
bool is_selected_item();

/**
 * @brief Checks the position of the selected item and handles collisions.
 *
 * This function checks if the selected item is within the game map bounds and if it collides with any other objects,
 * such as the panda, blocks, or planks. If a collision occurs or the item is out of bounds, the item is reset to its original position.
 */
void check_item_pos();

/**
 * @brief Updates the position of the selected item based on the cursor position.
 *
 * This function updates the position of the selected item by calculating the offset between the cursor position and the item's original position.
 */
void update_item_pos();

/**
 * @brief Updates the animation of the selected item.
 *
 * This function updates the animation frame of the selected item based on the user's input.
 * If the "R" key is pressed, the animation frame is incremented, otherwise, it is decremented.
 */
void update_item_animation();


/**
 * @brief Updates the inventory.
 *
 * This function updates the position of the items in the inventory.
 */
void update_inventory();

/**
 * @brief Selects an item based on the cursor's position.
 *
 * This function checks if any item that is in the inventory was selected by the user.
 *
 * @param item The item to check.
 * @return True if the item is selected, false otherwise.
 */
bool select_item(Sprite *item);
#endif
