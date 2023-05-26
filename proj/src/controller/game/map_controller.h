#ifndef _MAP_CONTROLLER_H_
#define _MAP_CONTROLLER_H_

#include "../KBC/KBC.h"
#include "../mouse/mouse.h"
#include "../keyboard/keyboard.h"
#include "../video/graphics.h"
#include "model/sprite.h"
#include "model/config.h"

extern Sprite* panda;
extern Sprite* item;

bool is_in_map(Sprite* item);
bool collide(Sprite* s1, Sprite* s2);


#endif 

