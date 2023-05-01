#ifndef _MODEL_H_
#define _MODEL_H_

#include <lcom/lcf.h>
#include "sprite.h"
#include "xpm/transformice.xpm"

typedef enum {
    MENU, 
    GAME,
    EXIT
} States;

void create_sprites();
void destroy_sprites();

#endif
