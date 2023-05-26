#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include <utils.h>
#include <i8042.h>

int (mouse_subscribe_int)(uint8_t* bit_no);

int (mouse_unsubscribe_int)();

int (mouse_enable_data_report)();

int (mouse_disable_data_report)();

int (read_outbuff)(uint8_t* data);

int (issue_command)(uint8_t reg, uint8_t cmd);

void (mouse_ih)();

int (parse_packet)(uint8_t byte_num, struct packet* pp);

int (parse_movement)(struct packet pp, uint8_t x_len, uint8_t tolerance, state_t state);

int (change_state)(state_t* state);
