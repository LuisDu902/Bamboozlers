#include "game_state.h"

extern uint8_t scancode;

extern Menu_state menu_state;

extern uint8_t *drawing_frame_buffer;
extern struct packet mouse_packet;

extern uint16_t yRes, xRes;

Item_state item_state = INIT;
Game_state game_state = INACTIVE;

Sprite *item;

uint16_t y_time = 0;

static int16_t ini_x, ini_y;
static int16_t off_x = 0;
static int16_t off_y = 0;

bool isRightPressed = false;
bool isLeftPressed = false;

void update_keyboard_game()
{

    read_scancode();

    switch (scancode)
    {
    case R_KEY:
        if (item_state == DRAG)
            item->i = (item->i + 1) % item->num_pixmaps;
        break;
    case E_KEY:
        if (item_state == DRAG)
            item->i = (item->i - 1 + item->num_pixmaps) % item->num_pixmaps;
        break;
    case ESC_BREAK:
        menu_state = EXIT;
        break;
    case ARROW_UP:
        if (game_state == INACTIVE || game_state == RUN)
        {
            y_time = 0;
            ini_y = panda->y;
            game_state = JUMP;
        }
        break;
    case ARROW_LEFT_PRESS:
        isLeftPressed = true;
        if (game_state == INACTIVE)
        {
            game_state = RUN;
        }
        break;
    case ARROW_LEFT_RELEASE:
        isLeftPressed = false;
        if (game_state == RUN)
        {
            game_state = INACTIVE;
        }
        break;
    case ARROW_RIGHT_PRESS:
        isRightPressed = true;
        if (game_state == INACTIVE)
        {
            game_state = RUN;
        }
        break;
    case ARROW_RIGHT_RELEASE:
        isRightPressed = false;
        if (game_state == RUN)
        {
            game_state = INACTIVE;
        }
        break;
    default:
        break;
    }
}

bool collide(Sprite *s1, Sprite *s2)
{
    if (s1 == s2)
        return false;

    uint16_t left = (s1->x > s2->x) ? s1->x : s2->x;
    uint16_t right = (s1->x + s1->width[s1->i] < s2->x + s2->width[s2->i]) ? s1->x + s1->width[s1->i] : s2->x + s2->width[s2->i];
    uint16_t top = (s1->y > s2->y) ? s1->y : s2->y;
    uint16_t bottom = (s1->y + s1->height[s1->i] < s2->y + s2->height[s2->i]) ? s1->y + s1->height[s1->i] : s2->y + s2->height[s2->i];

    for (int y = top; y < bottom; ++y)
    {
        for (int x = left; x < right; ++x)
        {
            uint32_t s1_color = s1->pixmap_array[s1->i][x - s1->x + (y - s1->y) * s1->width[s1->i]];
            uint32_t s2_color = s2->pixmap_array[s2->i][x - s2->x + (y - s2->y) * s2->width[s2->i]];

            if (s1_color != TRANSPARENT && s2_color != TRANSPARENT)
            {
                return true;
            }
        }
    }

    return false;
}

bool above(Sprite *s2)
{
    return (panda->y + panda->height[panda->i] == s2->y &&
            ((panda->x <= s2->x && s2->x <= panda->x + panda->width[panda->i]) ||
             (panda->x <= s2->x + s2->width[s2->i] && s2->x + s2->width[s2->i] <= panda->x + panda->width[panda->i]) ||
             (panda->x <= s2->x + s2->width[s2->i] && panda->x >= s2->x)));
}

bool is_in_map(Sprite *item)
{
    return item->x + item->width[item->i] <= 15 + MAP_WIDTH &&
           item->x >= 25 &&
           item->y + item->height[item->i] <= 20 + MAP_HEIGHT &&
           item->y >= 25;
}

void update_mouse_game()
{

    switch (item_state)
    {
    case INIT:
        if (mouse_packet.lb)
        {
            if (select_item(block) && !is_in_map(block))
            {
                off_x = cursor->x - block->x;
                off_y = cursor->y - block->y;
                ini_x = block->x;
                ini_y = block->y;

                item = block;
                item_state = DRAG;
            }
            if (select_item(little_plank) && !is_in_map(little_plank))
            {
                off_x = cursor->x - little_plank->x;
                off_y = cursor->y - little_plank->y;
                ini_x = little_plank->x;
                ini_y = little_plank->y;

                item = little_plank;

                item_state = DRAG;
            }
            if (select_item(big_plank) && !is_in_map(big_plank))
            {
                off_x = cursor->x - big_plank->x;
                off_y = cursor->y - big_plank->y;
                ini_x = big_plank->x;
                ini_y = big_plank->y;

                item = big_plank;
                item_state = DRAG;
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
                collide(item, big_plank))
            {

                item->x = ini_x;
                item->y = ini_y;
                item->i = 0;
            }

            item_state = INIT;
        }
        break;
    }
}

void update_hero_pos()
{

    if (game_state == INACTIVE){
        panda->i = 0;
    }
    if (!above(block) && !above(little_plank) && !above(big_plank) && panda->y + panda->height[panda->i] != 20 + MAP_HEIGHT && game_state != JUMP && game_state != FALL)
    {
        game_state = FALL;
        ini_y = panda->y;
    }
    if (isRightPressed || isLeftPressed)
    {
        panda->x += isRightPressed ? (XSPEED) : (-XSPEED);
        if (isRightPressed){ 
            if (panda->i == 0)panda->i =2;
            if (panda->i == 2) panda->i =8;
            else panda->i =2;
        }
        if (panda->x < 25)
            panda->x = 25;
        if (panda->x + panda->width[panda->i] > 15 + MAP_WIDTH)
            panda->x = 15 + MAP_WIDTH - panda->width[panda->i];

        if (collide(mouse, block))
        {
            game_state = INACTIVE;
            if (isRightPressed)
                panda->x = block->x - panda->width[panda->i];
            else
                panda->x = block->x + block->width[block->i];
        }
        else if (collide(mouse, little_plank))
        {
            game_state = INACTIVE;
            while (collide(mouse, little_plank)) {
                if (isRightPressed)
                    panda->x -= 1;
                else
                    panda->x += 1;
            }
        }
        else if (collide(mouse, big_plank))
        {
            game_state = INACTIVE;
            while (collide(mouse, big_plank)) {
                if (isRightPressed)
                    panda->x -= 1;
                else
                    panda->x += 1;
            }
        }
    }

    if (game_state == JUMP)
    {
        y_time++;

        panda->y = ini_y - YSPEED * y_time + y_time * y_time * (GRAVITY) / 2;
        panda->yspeed = YSPEED - GRAVITY * y_time;

        if (collide(mouse, block))
        {
            game_state = FALL;
            panda->y = block->y + block->height[block->i];
        }
        else if (collide(mouse, little_plank))
        {
            game_state = FALL;
            panda->y = little_plank->y + little_plank->height[little_plank->i];
        }
        else if (collide(mouse, big_plank))
        {
            game_state = FALL;
            panda->y = big_plank->y + big_plank->height[big_plank->i];
        }

        else if (panda->yspeed == 0)
        {
            ini_y = panda->y;
            y_time = 0;
            game_state = FALL;
        }
    }

    else if (game_state == FALL)
    {
        y_time++;

        panda->y = ini_y + y_time * y_time * (GRAVITY) / 2;
        panda->yspeed = GRAVITY * y_time;

        if (collide(mouse, block))
        {
            game_state = INACTIVE;
            panda->y = block->y - panda->height[panda->i];
        }
        else if (collide(mouse, little_plank))
        {
            game_state = INACTIVE;
            panda->y = little_plank->y - panda->height[panda->i];
        }
        else if (collide(mouse, big_plank))
        {
            game_state = INACTIVE;
            panda->y = big_plank->y - panda->height[panda->i];
        }
        else if (panda->y + panda->height[panda->i] >= 20 + MAP_HEIGHT)
        {
            panda->y = 20 + MAP_HEIGHT - panda->height[panda->i];
        }
        if (above(block) || above(little_plank) || above(big_plank) || panda->y + panda->height[panda->i] == 20 + MAP_HEIGHT)
        {
            game_state = INACTIVE;
        }
    }
}

