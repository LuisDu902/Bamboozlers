#ifndef _PANDA_CONTROLLER_H_
#define _PANDA_CONTROLLER_H_

#include "map_controller.h"


extern Sprite* panda;
extern Sprite* little_plank;
extern Sprite* big_plank;
extern Sprite* block;
extern Sprite* item;

Sprite* collide_item;

extern Game_state game_state;

extern bool isRightPressed;

bool above(Sprite *item);

void move_left();
void move_right();
void jump(uint32_t time, uint32_t y);
void fall(uint32_t time, uint32_t y);


bool hit_floor();
void handle_boundary_conditions();
bool collide_with_items();

void fix_collision();
void fix_jump_collision();
void fix_fall_collision();

void update_panda_animation();

#endif 

