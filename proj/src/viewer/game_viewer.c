#include "game_viewer.h"

int minutes=0;
int seconds=0;
extern int counter;

int (draw_game_menu)()
{    
    if (draw_map() != 0) return 1;
    if( draw_timer() != 0) return 1;
    if (draw_sprite(home)) return 1;
    if(draw_sprite(panda) != 0) return 1;
    if (draw_sprite(block) != 0) return 1;
    if (draw_sprite(little_plank) != 0) return 1;
    if (draw_sprite(big_plank) != 0) return 1;
    return 0;
}

int(draw_map)() {
    for (int i = 0; i < BORDER_WIDTH; i++) {
        if (vg_draw_hline(20, 20 + i, MAP_WIDTH, 0xFFFFFF)) return 1;
        if (vg_draw_hline(20, 480 + i, MAP_WIDTH, 0xFFFFFF)) return 1;
        if (vg_draw_vline(20 + i, 20, MAP_HEIGHT, 0xFFFFFF)) return 1;
        if (vg_draw_vline(775 + i, 20, MAP_HEIGHT, 0xFFFFFF)) return 1;
    }
    return 0;
}

int(draw_timer)(){
    
    if(counter % 30==0){
        seconds++;
        if(seconds%60==0){
            minutes++;
            seconds=0;
        }
    }
    timer[0]->i=minutes/10;
    timer[1]->i=minutes%10;
    timer[2]->i=seconds/10;
    timer[3]->i=seconds%10;
    if(draw_sprite(timer[0])!= 0) return 1;
    if(draw_sprite(timer[1])!= 0) return 1;
    if(draw_sprite(timer[2])!= 0) return 1;
    if(draw_sprite(timer[3])!= 0) return 1;

    return 0;
}
