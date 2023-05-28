#pragma once

#include <lcom/lcf.h>
#include "rtc_macros.h"




int (rtc_subscribe_int)(uint8_t* bit_no);


int (rtc_unsubscribe_int)();


int set_rtc_interrupts( bool value);


int (wait_until_finished_update)();


void (rtc_ih)();


int disable_update();


int enable_update();


int (rtc_read_info)(uint8_t reg, uint8_t* value);


void set_darkMode_alarm();



int (bcd_to_decimal)(uint8_t hex);


int (decimal_to_bcd)(uint8_t dec);

void (rtc_upd)();







