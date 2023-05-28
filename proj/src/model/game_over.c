#include "game_over.h"

#include "xpm/game_over_text.xpm"


void create_game_over_sprites()
{
    xpm_map_t game_over_text_pixmaps[] = {(xpm_map_t)game_over_text_xpm};
    xpm_map_t game_over_exit_pixmaps[] = {(xpm_map_t)game_over_exit_xpm,(xpm_map_t)game_over_exit_selected_xpm};
    xpm_map_t play_again_pixmaps[] = {(xpm_map_t)play_again_xpm,(xpm_map_t)play_again_selected_xpm};
    game_over_text = create_sprite_xpm(game_over_text_pixmaps, 1, 50, 100);
    play_again = create_sprite_xpm(play_again_pixmaps, 2, 51, 450);
    game_over_exit = create_sprite_xpm(game_over_exit_pixmaps, 2, 542, 450);
}

void destroy_game_over_sprites()
{
    destroy_sprite(game_over_text);
    
   
}
