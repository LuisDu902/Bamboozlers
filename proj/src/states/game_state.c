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

void update_keyboard_game(){
    read_scancode();

    switch (scancode){
        case R_KEY: case E_KEY:
            update_item_animation();
            break;

        case ESC_BREAK:
            menu_state = EXIT;
            break;

        case ARROW_UP:
         printf("CHECKING COLLISIONS???\n");
            if (game_state == INACTIVE || game_state == RUN){
                y_time = 0;
                ini_y = panda->y;
                game_state = JUMP;
            }
            break;

        case ARROW_LEFT_PRESS:
            isLeftPressed = true;
            if (game_state == INACTIVE) game_state = RUN;
            break;

        case ARROW_LEFT_RELEASE:
            panda->i = 3;
            isLeftPressed = false;
            if (game_state == RUN) game_state = INACTIVE;
            break;

        case ARROW_RIGHT_PRESS:
            isRightPressed = true;
            if (game_state == INACTIVE) game_state = RUN;
            break;

        case ARROW_RIGHT_RELEASE:
            panda->i = 0;
            isRightPressed = false;
            if (game_state == RUN) game_state = INACTIVE;
            break;
    }
}

void update_mouse_game(){
    switch (item_state){
        case INIT:
            if (mouse_packet.lb && is_selected_item()) item_state = DRAG;
            break;
        case DRAG:
            update_item_pos();
            if (!mouse_packet.lb){
                check_item_pos();
                item_state = INIT;
            }
    }
}

void update_panda_state(){
    if (!collide_with_items() && !hit_floor() && game_state != JUMP && game_state != FALL){
        game_state = FALL;
        ini_y = panda->y;
        y_time = 0;
    }
  printf("CHECKING COLLISIONS???\n");
    if (isRightPressed || isLeftPressed){
        isRightPressed ? move_right() : move_left();
        update_panda_animation();
        handle_boundary_conditions();
        printf("CHECKING COLLISIONS\n");
        if (collide_with_items()){
             printf("SHOULD\n");
            fix_collision();
            game_state = INACTIVE;
        }
    }

    switch (game_state){
        case JUMP:
            y_time++;

            jump(y_time, ini_y);

            if (collide_with_items()){
                fix_jump_collision();
                game_state = FALL;
                y_time = 0;
                ini_y = panda->y;
            }
            else if (panda->yspeed == 0){
                ini_y = panda->y;
                y_time = 0;
                game_state = FALL;
            }
            break;
    
        case FALL:
            y_time++;

            fall(y_time, ini_y);

            if (collide_with_items()){
                fix_fall_collision();
                game_state = INACTIVE;
            }

            if (hit_floor()){
                handle_boundary_conditions();
                game_state = INACTIVE;
            }
            break;

        default:
            break;
    }
}

