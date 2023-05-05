#include <lcom/lcf.h>
#include "state.h"

Menu_state menu_state = MENU;

void update_keyboard_state() {
    switch (menu_state){
        case MENU:
            update_keyboard_menu();
            break;
        case LEVEL_SELECTION:
            //update_keyboard_menu();
            return;
        case GAME:
            update_keyboard_game();
            break;
        case GAME_OVER:
            //update_keyboard_menu();
            return;
        case EXIT:
            return;
        default:
            break;
    } 
    draw_menu();
}
