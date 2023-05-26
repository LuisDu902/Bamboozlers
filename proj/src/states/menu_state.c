#include "menu_state.h"

extern uint8_t scancode;
extern Menu_state menu_state;
extern Sprite *mouse;

extern struct packet mouse_packet;
extern uint16_t yRes, xRes;

void update_keyboard_menu()
{
    read_scancode();

    switch (scancode)
    {
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

void update_mouse_menu()
{
    if (select_item (menu_play)){
        if (mouse_packet.lb){
            menu_state = GAME;
        }
    }
    if (select_item (instructions)){
        if (mouse_packet.lb){
            menu_state = GAME;
        }
    }
}
