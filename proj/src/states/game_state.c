#include "game_state.h"

extern uint8_t scancode;
extern Menu_state menu_state;
extern Sprite *mouse;

extern struct packet mouse_packet;
extern uint16_t yRes, xRes;

state_t state = INIT;
Sprite* current_item;

static int16_t ini_x, ini_y;
static int16_t off_x = 0;
static int16_t off_y = 0;

void update_keyboard_game()
{
    read_scancode();
    switch (scancode)
    {
    case ESC_BREAK:
        menu_state = EXIT;
        break;
    case ARROW_UP:
        mouse->y -= 20;
        if (mouse->y < 0)
            mouse->y = 0;
        break;
    case ARROW_DOWN:
        mouse->y += 20;
        if (mouse->y > yRes - mouse->height)
            mouse->y = yRes - mouse->height;
        break;
    case ARROW_LEFT:
        mouse->x -= 20;
        if (mouse->x < 0)
            mouse->x = 0;
        break;
    case ARROW_RIGHT:
        mouse->x += 20;
        if (mouse->x > xRes - mouse->width)
            mouse->x = xRes - mouse->width;
        break;
    default:
        break;
    }
}

bool select_item(Sprite* item)
{
    return cursor->x >= item->x && cursor->x <= item->x + item->width &&
           cursor->y >= item->y && cursor->y <= item->y + item->height;
}

bool collide(Sprite* s1, Sprite* s2){
    if (s1 == s2) return false;
    return (s1->x < s2->x + s2->width && 
    s1->x + s1->width > s2->x && 
    s1->y < s2->y + s2->height && 
    s1->y + s1->height > s2->y);

}

bool is_in_map(Sprite* item){
    return item->x + item->width <= map->x + map->width &&
            item->x >= map->x &&
            item->y + item->height <= map->y + map->height &&
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

                current_item = block;
                state = DRAG;
            }
            if (select_item(little_plank) && !is_in_map(little_plank)) {
                off_x = cursor->x - little_plank->x;
                off_y = cursor->y - little_plank->y;
                ini_x = little_plank->x;
                ini_y = little_plank->y;

                current_item = little_plank;

                state = DRAG;
            }
            if (select_item(big_plank) && !is_in_map(big_plank)) {
                off_x = cursor->x - big_plank->x;
                off_y = cursor->y - big_plank->y;
                ini_x = big_plank->x;
                ini_y = big_plank->y;

                current_item = big_plank;
                state = DRAG;
            }
        }
        break;

    case DRAG:
        current_item->x = cursor->x - off_x;
        current_item->y = cursor->y - off_y;
        
        if (!mouse_packet.lb)
        {
            if (!is_in_map(current_item) || 
            collide(current_item, mouse) || 
            collide(current_item, block) || 
            collide(current_item, little_plank) ||
            collide(current_item, big_plank)){
                
                current_item->x = ini_x;
                current_item->y = ini_y;
            }
            
            
             state = INIT;
        }
        break;
    }
}
