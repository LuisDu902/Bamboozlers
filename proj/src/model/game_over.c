#include "game_over.h"

#include "xpm/game_over_text.xpm"


void create_game_over_sprites()
{
    xpm_map_t game_over_text_pixmaps[] = {(xpm_map_t)game_over_text_xpm};
    game_over_text = create_sprite_xpm(game_over_text_pixmaps, 1, 220, 400);
}

void destroy_game_over_sprites()
{
    destroy_sprite(game_over_text);
    
   
}
