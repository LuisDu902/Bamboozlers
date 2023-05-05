#include "menu_state.h"

extern uint8_t scancode;
extern Menu_state menu_state;

void update_keyboard_menu(){
    read_scancode();

    switch (scancode) {
        case ENTER:
            menu_state = GAME;
            break;
        case ESC_BREAK:
            menu_state = EXIT;
            break;
        default:
            break;
    }
}
