#ifndef _ITEM_CONTROLLER_H_
#define _ITEM_CONTROLLER_H_

#include "map_controller.h"
#include "states/state.h"

int16_t item_x, item_y, off_x, off_y;

extern Sprite* little_plank;
extern Sprite* big_plank;
//extern Sprite* dirt_block_start;
//extern Sprite* dirt_block_end;
extern Sprite* little_block;
extern Sprite* big_block;
extern Sprite* panda;
extern Sprite* cursor;
extern uint8_t scancode;

Sprite* item;

bool is_selected_item();

void check_item_pos();
void update_item_pos();

void update_item_animation();

#endif 

