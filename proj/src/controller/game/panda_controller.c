#include "panda_controller.h"

bool above(Sprite *item)
{
    return (panda->y + panda->height[panda->i] <= item->y + 5);
}

void move_left()
{
    panda->x -= XSPEED;
}

void move_right()
{
    panda->x += XSPEED;
}

void jump(uint32_t time, uint32_t y)
{
    panda->y = y - YSPEED * time + time * time * (GRAVITY) / 2;
    panda->yspeed = YSPEED - GRAVITY * time;
}

void fall(uint32_t time, uint32_t y)
{
    panda->y = y + time * time * (GRAVITY) / 2;
    panda->yspeed = GRAVITY * time;
}

bool collide_with_items()
{
    if (collide(panda, block))
    {
        collide_item = block;
        return true;
    }
    else if (collide(panda, little_plank))
    {
        collide_item = little_plank;
        return true;
    }
    else if (collide(panda, big_plank))
    {
        collide_item = big_plank;
        return true;
    }
    return false;
}
bool hit_floor()
{
    return panda->y + panda->height[panda->i] > 20 + MAP_HEIGHT;
}
void handle_boundary_conditions()
{
    if (panda->x < 25)
        panda->x = 25;
    if (panda->x + panda->width[panda->i] > 15 + MAP_WIDTH)
        panda->x = 15 + MAP_WIDTH - panda->width[panda->i];
    if (panda->y + panda->height[panda->i] >= 20 + MAP_HEIGHT)
        panda->y = 20 + MAP_HEIGHT - panda->height[panda->i];
}

void fix_collision()
{
    if (!above(collide_item))
    {
        while (collide(panda, collide_item))
            panda->x += isRightPressed ? -1 : 1;
    }
}

void fix_jump_collision()
{
    while (collide(panda, collide_item))
        panda->y++;
}

void fix_fall_collision()
{
    while (collide(panda, collide_item))
        panda->y--;
}

void update_panda_animation()
{

    if (game_state == JUMP)
    {
        panda->i = 6;
    }
    else
    {
        if (isRightPressed)
        {
            if (panda->i > 2)
                panda->i = 0;
            panda->i = (panda->i + 1) % 3;
        }
        else
        {
            if (panda->i < 3)
                panda->i = 3;
            panda->i = (panda->i + 1) % 3 + 3;
        }
    }
}