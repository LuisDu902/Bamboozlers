#include "game_over_viewer.h"


int (draw_game_over_menu)()
{    
    
    if (draw_sprite(game_over_text)) return 1;
    if (draw_sprite(play_again)) return 1;
    if (draw_sprite(game_over_exit)) return 1;
    
    return 0;
}
