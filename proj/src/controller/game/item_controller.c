#include "item_controller.h"

bool is_selected_item()
{
    if (select_item(block) && !is_in_map(block))
        item = block;
    if (select_item(little_plank) && !is_in_map(little_plank))
        item = little_plank;
    if (select_item(big_plank) && !is_in_map(big_plank))
        item = big_plank;

    if (item != NULL)
    {
        off_x = cursor->x - item->x;
        off_y = cursor->y - item->y;
        item_x = item->x;
        item_y = item->y;
        return true;
    }
    return false;
}

void update_item_pos()
{
    item->x = cursor->x - off_x;
    item->y = cursor->y - off_y;
}

void check_item_pos()
{

    if (!is_in_map(item) || collide(item, panda) || collide(item, block) || collide(item, little_plank) || collide(item, big_plank))
    {
        item->x = item_x;
        item->y = item_y;
        item->i = 0;
    }
   
    item = NULL;
}

void update_item_animation()
{
    if (scancode == R_KEY)
        item->i = (item->i + 1) % item->num_pixmaps;
    else 
        item->i = (item->i - 1 + item->num_pixmaps) % item->num_pixmaps;
}
