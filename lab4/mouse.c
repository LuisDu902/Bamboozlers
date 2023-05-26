#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include <mouse.h>

int mouse_hook_id = MOUSE_IRQ;
bool value = false;
uint8_t curr_byte, status;

static movement_t move = OTHER;
static int8_t x = 0, y = 0;


int (mouse_subscribe_int)(uint8_t* bit_no){
    *bit_no = mouse_hook_id;
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_int)(){
    return sys_irqrmpolicy(&mouse_hook_id);
}

int (mouse_enable_data_report)(){
    uint8_t result;
    while (1){
        if (issue_command(KBC_ST_REG, MOUSE_CMD_BYTE)) return 1;
        if (issue_command(WRITE_CMD_BYTE, ENABLE_CMD)) return 1;
        if (read_outbuff(&result)) return 1;
        if (result == MOUSE_ACK) return 0;
        if (result == MOUSE_NACK || result == MOUSE_ERROR) return 1;
        tickdelay(micros_to_ticks(DELAY_US));
    }
}

int (mouse_disable_data_report)(){
    uint8_t result;
    while (1){
        if (issue_command(KBC_ST_REG, MOUSE_CMD_BYTE)) return 1;
        if (issue_command(WRITE_CMD_BYTE, DISABLE_CMD)) return 1;
        if (read_outbuff(&result)) return 1;
        if (result == MOUSE_ACK) return 0;
        if (result == MOUSE_NACK || result == MOUSE_ERROR) return 1;
        tickdelay(micros_to_ticks(DELAY_US));
    }
}

int (read_outbuff)(uint8_t* data){
    while( 1 ) {
        if (util_sys_inb(KBC_ST_REG, &status)) return 1;
        if( status & KBC_OBF ) {
            if (util_sys_inb(KBC_OUT_BUF, data)) return 1;
            if ( (status & (KBC_ERROR)) == 0 )
                return 0;
            else
                return 1;
        }
        tickdelay(micros_to_ticks(DELAY_US));
    }
}

int (issue_command)(uint8_t reg, uint8_t cmd){
    while( 1 ) {
        if (util_sys_inb(KBC_ST_REG, &status)) return 1;
    if( (status & KBC_IBF) == 0 ) {
        return (sys_outb(reg, cmd));
    }
    tickdelay(micros_to_ticks(DELAY_US));
}
}

void (mouse_ih)(){
    if (read_outbuff(&curr_byte)){
        value = true;
        return;
    }
}

int (parse_packet)(uint8_t byte_num, struct packet* pp){
    if (byte_num == 0){
        if (curr_byte & BIT(3)){
            pp->bytes[byte_num] = curr_byte;
            pp->y_ov = curr_byte & BIT(7);
            pp->x_ov = curr_byte & BIT(6);
            pp->delta_y = (curr_byte & BIT(5)) ? 0xFF00 : 0x0000;
            pp->delta_x = (curr_byte & BIT(4)) ? 0xFF00 : 0x0000;
            pp->mb = curr_byte & BIT(2);
            pp->rb = curr_byte & BIT(1);
            pp->lb = curr_byte & BIT(0);
            return 0;
        }
    }
    else if (byte_num == 1){
        pp->bytes[byte_num] = curr_byte;
        pp->delta_x |= curr_byte;
        return 0;
    }
    else if (byte_num == 2){
        pp->bytes[byte_num] = curr_byte;
        pp->delta_y |= curr_byte;
        return 0;
    }
    return 1;
}

int (parse_movement)(struct packet pp, uint8_t x_len, uint8_t tolerance, state_t state){
    
    if (pp.lb && !pp.mb && !pp.rb){
        if ((pp.delta_x >= 0 && pp.delta_y >= 0) || (pp.delta_x * -1 < tolerance && pp.delta_y * -1 < tolerance)){
            x += pp.delta_x;
            y += pp.delta_y;
            move = L_MOVE;
        }
        else{
            x = 0;
            y = 0;
            move = OTHER;
        }
    }
    else if (!pp.lb && !pp.mb && pp.rb){
        if ((pp.delta_x >= 0 && pp.delta_y <= 0) || (pp.delta_x * -1 < tolerance && pp.delta_y < tolerance)){
            x += pp.delta_x;
            y += pp.delta_y;
            move = R_MOVE;
        }
        else{
            x = 0;
            y = 0;
            move = OTHER;
        }
    }
    else if (!pp.lb && !pp.mb && !pp.rb){
        if (x >= x_len && abs(pp.delta_x) <= tolerance && abs(pp.delta_y) <= tolerance && abs(y)/abs(x) > 1){
            x = 0;
            y = 0;
            move = MOV_END;
        }
        else if (abs(pp.delta_x) <= tolerance && abs(pp.delta_y) <= tolerance){
            x = 0;
            y = 0;
            move = NO_MOVE;
        }
        else{
            x = 0;
            y = 0;
            move = OTHER;
        }
    }
    else{
        x = 0;
        y = 0;
        move = OTHER;
    }
    return 0;
}

int (change_state)(state_t* state){
    switch (*state){
    case INIT:
        if (move == L_MOVE) *state = LEFT;
        break;
    case LEFT:
        if (move == L_MOVE) break;
        else if (move == MOV_END) *state = VERTEX;
        else *state = INIT;
        break;
    case VERTEX:
        if (move == NO_MOVE) break;
        else if (move == R_MOVE) *state = RIGHT;
        else *state = INIT;
        break;
    case RIGHT:
        if (move == R_MOVE) break;
        else if (move == MOV_END) *state = END;
        else *state = INIT;
        break;
    default:
        return 1;
    }
    return 0;
}
