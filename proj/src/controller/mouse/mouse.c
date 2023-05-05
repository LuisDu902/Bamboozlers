#include <lcom/lcf.h>

#include <stdint.h>

#include "mouse.h"

int mouse_hook_id = 2;

uint8_t byte;

int error = 1;

int mouse_subscribe_int(uint32_t *bit_no) {
    *bit_no = BIT(mouse_hook_id);
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE,&mouse_hook_id);
}

int mouse_unsubscribe_int() {
    return sys_irqrmpolicy(&mouse_hook_id);
}

void (mouse_ih)(){
    error = read_output(KBC_OUT_BUF, &byte, false);
}

int (parse_packet)(uint8_t byte_no, struct packet *pp){
  
    pp->bytes[byte_no] = byte;
                        
    switch (byte_no) {
        case 0:
            pp->y_ov = byte & BIT(7);
            pp->x_ov = byte & BIT(6);
            pp->delta_y = (byte & BIT(5)) ? 0xFF00 : 0x0000;
            pp->delta_x = (byte & BIT(4)) ? 0xFF00 : 0x0000;
            pp->mb = byte & BIT(2);
            pp->rb = byte & BIT(1);
            pp->lb = byte & BIT(0);
            break;
        case 1:
            pp->delta_x |= byte;
            break;
        case 2:
            pp->delta_y |= byte;
            break;
    }

    return 0;
}


int disable_data_reporting(){

    uint8_t cmd;
    int attempts = 10;

    while (attempts--){

        if (write_command(KBC_IN_BUF, WRITE_BYTE_TO_MOUSE) != 0) return 1;

        if (write_command(KBC_CMD_REG, DISABLE_DATA_REPORTING) != 0) return 1;

        WAIT_KBC;

        if (util_sys_inb(KBC_OUT_BUF, &cmd) != 0) return 1;

        if (cmd == MOUSE_ACK) return 0;

    }
    return 1;
}

int enable_data_reporting(){

    uint8_t cmd;
    int attempts = 10;

    while (attempts--){

        if (write_command(KBC_IN_BUF, WRITE_BYTE_TO_MOUSE) != 0) return 1;

        if (write_command(KBC_CMD_REG, ENABLE_DATA_REPORTING) != 0) return 1;

        WAIT_KBC;

        if (util_sys_inb(KBC_OUT_BUF, &cmd) != 0) return 1;

        if (cmd == MOUSE_ACK) return 0;

    }
    return 1;  
}

