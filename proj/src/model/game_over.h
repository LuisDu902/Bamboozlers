#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_

#include "sprite.h"

Sprite *game_over_text;
Sprite *play_again;
Sprite *game_over_exit;



void create_game_over_sprites();
void destroy_game_over_sprites();

#endif
