#ifndef _VIEWER_H_
#define _VIEWER_H_

#include "controller/video/graphics.h"
#include "model/model.h"
#include "states/state.h"
#include "game_viewer.h"
#include "menu_viewer.h"
#include "instructions_viewer.h"
#include "game_over_viewer.h"
#include "level_select_viewer.h"

int (draw_sprite)(Sprite *sprite);

int (draw_menu)();

int (draw_cursor)();
#endif
