#include "game_state.h"

extern uint8_t scancode;

extern Menu_state menu_state;

extern uint8_t* drawing_frame_buffer;
extern struct packet mouse_packet;

extern uint16_t yRes, xRes;

state_t state = INIT;
Sprite* item;
static int16_t ini_x, ini_y;
static int16_t off_x = 0;
static int16_t off_y = 0;

void update_keyboard_game()
{
    read_scancode();

    switch (scancode) {
    case R_KEY: 
        if (state == DRAG)
            item->current_pixmap = (item->current_pixmap + 1) % item->num_pixmaps;
        break;
    case E_KEY: 
        if (state == DRAG)
            item->current_pixmap = (item->current_pixmap - 1 + item->num_pixmaps) % item->num_pixmaps;
        break;
    case ESC_BREAK:
        menu_state = EXIT;
        break;
    case ARROW_UP:
        mouse->y -= 10;
        if (mouse->y < 0)
            mouse->y = 0;
        break;
    case ARROW_DOWN:
        mouse->y += 10;
        if (mouse->y > yRes - mouse->height[mouse->current_pixmap])
            mouse->y = yRes - mouse->height[mouse->current_pixmap];
        break;
    case ARROW_LEFT:
        mouse->x -= 10;
        if (mouse->x < 0)
            mouse->x = 0;
        break;
    case ARROW_RIGHT:
        mouse->x += 10;
        if (mouse->x > xRes - mouse->width[mouse->current_pixmap])
            mouse->x = xRes - mouse->width[mouse->current_pixmap];
        break;
    default:
        break;
    }
}

bool collide(Sprite* s1, Sprite* s2){
    if (s1 == s2) return false;
    return (s1->x < s2->x + s2->width[s2->current_pixmap] && 
    s1->x + s1->width[s1->current_pixmap] > s2->x && 
    s1->y < s2->y + s2->height[s2->current_pixmap] && 
    s1->y + s1->height[s1->current_pixmap] > s2->y);

}

bool is_in_map(Sprite* item){
    return item->x + item->width[item->current_pixmap] <= map->x + map->width[map->current_pixmap] &&
            item->x >= map->x &&
            item->y + item->height[item->current_pixmap] <= map->y + map->height[map->current_pixmap] &&
            item->y >= map->y;
}

void update_mouse_game()
{

    switch (state)
    {
    case INIT:
        if (mouse_packet.lb) {
            if (select_item(block) && !is_in_map(block)) {
                off_x = cursor->x - block->x;
                off_y = cursor->y - block->y;
                ini_x = block->x;
                ini_y = block->y;

                item = block;
                state = DRAG;
            }
            if (select_item(little_plank) && !is_in_map(little_plank)) {
                off_x = cursor->x - little_plank->x;
                off_y = cursor->y - little_plank->y;
                ini_x = little_plank->x;
                ini_y = little_plank->y;

                item = little_plank;

                state = DRAG;
            }
            if (select_item(big_plank) && !is_in_map(big_plank)) {
                off_x = cursor->x - big_plank->x;
                off_y = cursor->y - big_plank->y;
                ini_x = big_plank->x;
                ini_y = big_plank->y;

                item = big_plank;
                state = DRAG;
            }
        }
        break;

    case DRAG:
        item->x = cursor->x - off_x;
        item->y = cursor->y - off_y;
        
        if (!mouse_packet.lb)
        {
            if (!is_in_map(item) || 
            collide(item, mouse) || 
            collide(item, block) || 
            collide(item, little_plank) ||
            collide(item, big_plank)){
                
                item->x = ini_x;
                item->y = ini_y;
                item->current_pixmap = 0;

            }
            
            
             state = INIT;
        }
        break;
    }
}
