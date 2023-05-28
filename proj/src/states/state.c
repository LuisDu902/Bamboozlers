#include "state.h"

Menu_state menu_state = MENU;
Level_state level_state = LEVEL_ONE;

extern uint8_t byte_no;
Item_state item_state = INIT;
Panda_state panda_state = INACTIVE;

uint32_t y_time = 0;

int16_t ini_y;

bool isRightPressed = false;
bool isLeftPressed = false;

extern struct packet mouse_packet;

extern Item_state item_state;

void update_keyboard_state()
{
    switch (menu_state)
    {
    case MENU:
        update_keyboard_menu();
        break;
    case LEVEL_SELECTION:
        update_keyboard_level();
        break;
    case GAME:
        update_keyboard_game();
        break;
    case INSTRUCTIONS:
        update_keyboard_instructions();
        break;
    case GAME_OVER:
        update_keyboard_game_over();
        return;
    default:
        return;
    }
}

void update_mouse_state()
{
    mouse_ih();
    sync_packet();
    if (byte_no == 3)
    {
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
            update_mouse_level();
            break;
        case GAME_OVER:
            update_mouse_game_over();
            break;
        default:
            break;
        }
    }
}

void update_timer_state()
{
    if (menu_state == GAME)
    {
        update_timer_game();
    }
    draw_menu();
    draw_cursor();
    swap_buffers();
    clear_drawing_buffer();
}

void update_cursor_position()
{
    if (mouse_packet.y_ov || mouse_packet.x_ov) return;

    int16_t new_x = cursor->x + mouse_packet.delta_x;
    int16_t new_y = cursor->y - mouse_packet.delta_y;

    if (new_x < 0)
        cursor->x = 0;
    else if (new_x >= (xRes - cursor->width[cursor->i]))
        cursor->x = (xRes - cursor->width[cursor->i]);
    else
        cursor->x = new_x;

    if (new_y < 0)
        cursor->y = 0;
    else if (new_y >= (yRes - cursor->height[cursor->i]))
        cursor->y = (yRes - cursor->height[cursor->i]);
    else
        cursor->y = new_y;
}



void update_keyboard_game_over()
{
    read_scancode();

    switch (scancode)
    {
    case ENTER: case Q_KEY:
        menu_state = MENU;
        break;
    case ESC_BREAK:
        menu_state = EXIT;
        break;
    
    }
}

void update_mouse_game_over()
{
   
   if (mouse_packet.lb)
    {
        if (select_item(play_again))
        {
            menu_state = LEVEL_SELECTION;
        }

        else if (select_item(game_exit))
        {
            menu_state = EXIT;
        }
    }
}

void update_keyboard_instructions()
{
    read_scancode();

    switch (scancode)
    {
    case ENTER: case Q_KEY: 
        menu_state = MENU;
        break;
    case ESC_BREAK:
        menu_state = EXIT;
        break;
    
    }
}


void update_keyboard_menu()
{
    read_scancode();

    switch (scancode)
    {
    case ENTER:
        menu_state = LEVEL_SELECTION;
        break;
    case ESC_BREAK:
        menu_state = EXIT;
        break;
    default:
        break;
    }
}

void update_mouse_menu()
{
    if (mouse_packet.lb)
    {
        if (select_item(levels))
        {
            menu_state = LEVEL_SELECTION;
        }

        else if (select_item(instructions))
        {
            menu_state = INSTRUCTIONS;
        }
    }
}


void update_keyboard_level()
{
    read_scancode();

    switch (scancode)
    {
    case Q_KEY:
        menu_state = MENU;
        break;
    case ESC_BREAK:
        menu_state = EXIT;
        break;
    default:
        break;
    }
}

void update_mouse_level()
{

    if (mouse_packet.lb)
    {
        if (select_item(level_one))
        {
            map_set_up(0);
            menu_state = GAME;
        }

        else if (select_item(level_two) && level_state != LEVEL_ONE)
        {
            map_set_up(1);
            menu_state = GAME;
        }

        else if (select_item(level_three) && level_state == LEVEL_THREE)
        {
            map_set_up(2);
            menu_state = GAME;
        }
    }
}

void update_keyboard_game()
{
    read_scancode();

    switch (scancode)
    {
    case Q_KEY:
        menu_state = LEVEL_SELECTION;
        break;
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
        if (panda_state == INACTIVE || panda_state == RUN)
        {
            y_time = 0;
            ini_y = panda->y;
            panda_state = JUMP;
        }
        break;

    case ARROW_LEFT_PRESS:
        /* go to run state */
        isLeftPressed = true;
        if (panda_state == INACTIVE)
            panda_state = RUN;
        break;

    case ARROW_LEFT_RELEASE:
        /* go back to idle state */
        panda->i = 3;
        isLeftPressed = false;
        if (panda_state == RUN)
        {

            panda_state = INACTIVE;
        }
        break;

    case ARROW_RIGHT_PRESS:
        /* go to run state */
        isRightPressed = true;
        if (panda_state == INACTIVE)
            panda_state = RUN;
        break;

    case ARROW_RIGHT_RELEASE:
        /* go back to idle state */
        panda->i = 0;
        isRightPressed = false;

        if (panda_state == RUN)
        {

            panda_state = INACTIVE;
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

void update_timer_game()
{
    if (panda_state == DEAD)
        menu_state = GAME_OVER;
    else if (collide(panda, home) && !is_in_map(bamboo))
    {
        menu_state = MENU;
        level_state = (level_state == LEVEL_ONE) ? LEVEL_TWO : LEVEL_THREE;
    }
    else
    {
        timer_int_handler();
        if (item_state == INIT)
            update_panda_state();
    }
}

void update_panda_state()
{

    if (collide(panda, bamboo))
    {
        update_inventory();
    }
    /* if there's nothing below the panda, it should fall */
    if (panda_state != JUMP && panda_state != FALL && !above_any_item())
    {
        panda_state = FALL;
        ini_y = panda->y;
        y_time = 0;
    }

    if (hit_floor() || collide(panda, lava))
    {
        panda_state = DEAD;
        return;
    }

    switch (panda_state)
    {
    case JUMP:

        /* update the panda pos */
        y_time++;
        jump(y_time, ini_y);

        /* if the panda hits the roof */
        if (panda->y < 25)
        {
            handle_boundary_conditions();
            panda_state = FALL;
            y_time = 0;
            ini_y = panda->y;
        }

        /* if the move causes a collision with any item */
        if (collide_with_items())
        {

            /* correct the panda pos */
            fix_jump_collision();

            /* the panda should fall if it collides */
            panda_state = FALL;
            y_time = 0;
            ini_y = panda->y;
        }

        /* if the panda has ended the jump successfully, it should fall */
        else if (panda->yspeed == 0)
        {
            ini_y = panda->y;
            y_time = 0;
            panda_state = FALL;
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
            panda_state = INACTIVE;
        }

        /* if the panda hits the floor */
        else if (hit_floor())
        {
            panda_state = DEAD;
            return;
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
            panda_state = INACTIVE;
        }
    }
}

