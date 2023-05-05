#ifndef _VIEWER_H_
#define _VIEWER_H_

#include <lcom/lcf.h>
#include "controller/video/graphics.h"
#include "model/model.h"
#include "states/state.h"
#include "game_viewer.h"
#include "menu_viewer.h"

int (draw_sprite)(Sprite *sprite);

int (draw_menu)();

#endif
