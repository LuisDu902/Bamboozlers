#include "game_state.h"

extern uint8_t scancode;
extern Menu_state menu_state;
extern Sprite* mouse;

void update_keyboard_game(){
    read_scancode();
    switch (scancode) {
        case ESC_BREAK:
            menu_state = EXIT;
            break;
        case ARROW_UP:
            mouse->y -= 20;
            if (mouse->y < 0) mouse->y = 0;
            break;
        case ARROW_DOWN:
            mouse->y += 20;
            if (mouse->y > mode_info.YResolution - mouse->height) mouse->y = mode_info.YResolution - mouse->height;   
            break;
        case ARROW_LEFT:
            mouse->x -= 20;
            if (mouse->x < 0) mouse->x = 0;
            break;
        case ARROW_RIGHT:
            mouse->x += 20;
            if (mouse->x > mode_info.XResolution - mouse->width) mouse->x = mode_info.XResolution - mouse->width;
            break;    
        default:
            break;
    }
}

