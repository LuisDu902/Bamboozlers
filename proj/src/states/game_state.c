#include "game_state.h"

extern uint8_t scancode;

extern Menu_state menu_state;

extern uint8_t *drawing_frame_buffer;
extern struct packet mouse_packet;

extern uint16_t yRes, xRes;

Item_state item_state = INIT;
Game_state game_state = INACTIVE;

uint32_t y_time = 0;

int16_t ini_y;

bool isRightPressed = false;
bool isLeftPressed = false;

void update_keyboard_game()
{
    read_scancode();

    switch (scancode)
    {
    case R_KEY:
    case E_KEY:
        if (item_state == DRAG)
            update_item_animation();
        break;

    case ESC_BREAK:
        menu_state = EXIT;
        break;

    case ARROW_UP:
        /* go to jump state */
        if (game_state == INACTIVE || game_state == RUN)
        {
            y_time = 0;
            ini_y = panda->y;
            game_state = JUMP;
        }
        break;

    case ARROW_LEFT_PRESS:
        /* go to run state */
        isLeftPressed = true;
        if (game_state == INACTIVE)
            game_state = RUN;
        break;

    case ARROW_LEFT_RELEASE:
        /* go back to idle state */
        panda->i = 3;
        isLeftPressed = false;
        if (game_state == RUN)
        {
            
            game_state = INACTIVE;
        }
        break;

    case ARROW_RIGHT_PRESS:
        /* go to run state */
        isRightPressed = true;
        if (game_state == INACTIVE)
            game_state = RUN;
        break;

    case ARROW_RIGHT_RELEASE:
        /* go back to idle state */
        panda->i = 0;
        isRightPressed = false;
    
        if (game_state == RUN)
        {
           
            game_state = INACTIVE;
        }
        break;
    }
}

void update_mouse_game()
{
    switch (item_state)
    {
    case INIT:
        if (mouse_packet.lb && is_selected_item())
            item_state = DRAG;
        break;
    case DRAG:
        update_item_pos();
        if (!mouse_packet.lb)
        {
            check_item_pos();
            item_state = INIT;
        }
    }
}

void update_panda_state()
{

    /* if there's nothing below the panda, it should fall */
    if (game_state != JUMP && game_state != FALL && !above_any_item() && !hit_floor())
    {
        game_state = FALL;
        ini_y = panda->y;
        y_time = 0;
    }

    switch (game_state)
    {
    case JUMP:

        /* update the panda pos */
        y_time++;
        jump(y_time, ini_y);

        /* if the move causes a collision with any item */
        if (collide_with_items())
        {

            /* correct the panda pos */
            fix_jump_collision();

            /* the panda should fall if it collides */
            game_state = FALL;
            y_time = 0;
            ini_y = panda->y;
        }

        /* if the panda has ended the jump successfully, it should fall */
        else if (panda->yspeed == 0)
        {
            ini_y = panda->y;
            y_time = 0;
            game_state = FALL;
        }
        break;

    case FALL:

        /* update the panda pos */
        y_time++;
        fall(y_time, ini_y);

        /* if the move causes a collision with any item */
        if (collide_with_items())
        {

            /* correct the panda pos */
            fix_fall_collision();
            game_state = INACTIVE;
        }

        /* if the panda hits the floor */
        else if (hit_floor())
        {
            /* correct the panda pos */
            handle_boundary_conditions();
            game_state = INACTIVE;
        }
        break;

    default:
        break;
    }
     /* if the panda moves left or right */
    if (isRightPressed || isLeftPressed)
    {
        /* update the panda pos */
        isRightPressed ? move_right() : move_left();
        update_panda_animation();

        /* handle left and right bounds */
        handle_boundary_conditions();

        /* if the move causes a collision with any item */
        if (collide_with_items())
        {
            /* correct the panda pos */
            fix_collision();
            game_state = INACTIVE;
        }
    }

}
