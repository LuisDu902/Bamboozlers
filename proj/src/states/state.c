#include <lcom/lcf.h>
#include "state.h"

Menu_state menu_state = MENU;

extern uint8_t byte_no;

extern struct packet mouse_packet;

void update_keyboard_state()
{
    switch (menu_state)
    {
    case MENU:
        update_keyboard_menu();
        break;
    case LEVEL_SELECTION:
        // update_keyboard_menu();
        return;
    case GAME:
        update_keyboard_game();
        break;
    case GAME_OVER:
        // update_keyboard_menu();
        return;
    case EXIT:
        return;
    default:
        break;
    }
}

void update_mouse_state()
{
    mouse_ih();
    sync_packet();
    if (byte_no == 3){
        byte_no = 0;
        update_cursor_position();
        switch (menu_state)
        {
        case MENU: case GAME:
            update_mouse_menu();
            break;
        case LEVEL_SELECTION:
        case GAME_OVER:
        case EXIT:
            return;
        default:
            break;
        }
    }
    
}

void update_timer_state()
{
    draw_menu();
    draw_cursor();
    swap_buffers();
    clear_drawing_buffer();
}


void update_cursor_position(){
    if (mouse_packet.y_ov|| mouse_packet.x_ov) return;

    int16_t new_x = cursor->x + mouse_packet.delta_x;
    int16_t new_y = cursor->y - mouse_packet.delta_y;

    if (new_x < 0) cursor->x = 0;
    else if (new_x >= (xRes-cursor->width)) cursor->x = (xRes-cursor->width);
    else cursor->x = new_x;

    if (new_y < 0) cursor->y = 0;
    else if (new_y >= (yRes-cursor->height)) cursor->y = (yRes-cursor->height);
    else cursor->y = new_y;

}
