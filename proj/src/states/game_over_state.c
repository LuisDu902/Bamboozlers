#include "menu_state.h"

extern uint8_t scancode;
extern Menu_state menu_state;

extern struct packet mouse_packet;
extern uint16_t yRes, xRes;

void update_keyboard_game_over()
{
    read_scancode();

    switch (scancode)
    {
    case ENTER:
        menu_state = MENU;
        break;
    case ESC_BREAK:
        menu_state = EXIT;
        break;
    
    }
}

void update_mouse_game_over()
{
   
   
}
