#include "game_state.h"

extern uint8_t scancode;

extern Menu_state menu_state;

extern uint8_t *drawing_frame_buffer;
extern struct packet mouse_packet;

extern uint16_t yRes, xRes;

Item_state item_state = INIT;
Game_state game_state = INACTIVE;

Sprite *item;

uint16_t jump_time = 0;

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
            jump_time = 0;
            ini_y = mouse->y;
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
    return (s1->x < s2->x + s2->width[s2->i] &&
            s1->x + s1->width[s1->i] > s2->x &&
            s1->y < s2->y + s2->height[s2->i] &&
            s1->y + s1->height[s1->i] > s2->y);
}

bool above(Sprite *s2)
{
    return (mouse->y + mouse->height[mouse->i] == s2->y &&
            ((mouse->x >= s2->x && mouse->x <= s2->x + s2->width[s2->i]) ||
            (mouse->x + mouse->width[mouse->i] <= s2->x + s2->width[s2->i] && mouse->x + mouse->width[mouse->i]  >= s2->x))
    );
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
    if (!above(block) && !above(little_plank) && !above(big_plank) && mouse->y + mouse->height[mouse->i] != 20 + MAP_HEIGHT && game_state != JUMP && game_state != FALL){
        printf("IT SHOULD FALL\n");
        game_state = FALL;
        ini_y = mouse->y;
    }
    if (isRightPressed || isLeftPressed)
    {
        mouse->x += isRightPressed ? (XSPEED) : (-XSPEED);
        if (mouse->x < 25)
            mouse->x = 25;
        if (mouse->x + mouse->width[mouse->i] > 15 + MAP_WIDTH)
            mouse->x = 15 + MAP_WIDTH - mouse->width[mouse->i];
    }


    if (game_state == JUMP){
        jump_time++;

        mouse->y = ini_y - YSPEED * jump_time + jump_time * jump_time * (GRAVITY) / 2;
        mouse->yspeed = YSPEED - GRAVITY * jump_time;

        if (collide(mouse, block)){
            game_state = FALL;
            mouse->y = block->y+block->height[block->i];
            printf("isAbove : %d\n", above(block));
        }
        else if (collide(mouse, little_plank)){
            game_state = FALL;
            mouse->y = little_plank->y+little_plank->height[little_plank->i];
            printf("isAbove : %d\n", above(block));
        }
        else if (collide(mouse, big_plank)){
            game_state = FALL;
            mouse->y = big_plank->y + big_plank->height[big_plank->i];
            printf("isAbove : %d\n", above(block));
        }

        else if (mouse->yspeed == 0)
        {
            ini_y = mouse->y;
            jump_time = 0;
            game_state = FALL;
        }
    }

    else if (game_state == FALL)
    {
        jump_time++;
       
        mouse->y = ini_y + jump_time * jump_time * (GRAVITY) / 2;
        mouse->yspeed = GRAVITY * jump_time;
         printf("(%d,%d,%d)\n", mouse->y, mouse->yspeed, jump_time);

        if (collide(mouse, block)){
            game_state = INACTIVE;
            mouse->y = block->y-mouse->height[mouse->i];
            printf("isAbove : %d\n", above(block));
        }
        else if (collide(mouse, little_plank)){
            game_state = INACTIVE;
            mouse->y = little_plank->y-mouse->height[mouse->i];
            printf("isAbove : %d\n", above(block));
        }
        else if (collide(mouse, big_plank)){
            game_state = INACTIVE;
            mouse->y = big_plank->y-mouse->height[mouse->i];
            printf("isAbove : %d\n", above(block));
        }
        else if (mouse->y  + mouse->height[mouse->i]>= 20 + MAP_HEIGHT){
            mouse->y = 20 + MAP_HEIGHT - mouse->height[mouse->i];
        }
         if (above(block) || above(little_plank) || above(big_plank) || mouse->y + mouse->height[mouse->i] == 20 + MAP_HEIGHT)
        {
            game_state = INACTIVE;
            printf("isAbove : %d\n", above(block));
        }
    }
}
