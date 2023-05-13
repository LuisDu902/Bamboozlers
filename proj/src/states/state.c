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
        case MENU:
            update_mouse_menu();
            break;
        case GAME:
            update_mouse_game();
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
    else if (new_x >= (xRes-cursor->width[cursor->current_pixmap])) cursor->x = (xRes-cursor->width[cursor->current_pixmap]);
    else cursor->x = new_x;

    if (new_y < 0) cursor->y = 0;
    else if (new_y >= (yRes-cursor->height[cursor->current_pixmap])) cursor->y = (yRes-cursor->height[cursor->current_pixmap]);
    else cursor->y = new_y;

}

bool select_item(Sprite* item)
{
    return cursor->x >= item->x && cursor->x <= item->x + item->width[item->current_pixmap] &&
           cursor->y >= item->y && cursor->y <= item->y + item->height[item->current_pixmap] ;
           //&& get_pixel_color(cursor->x, cursor->y) != 0;           
}
