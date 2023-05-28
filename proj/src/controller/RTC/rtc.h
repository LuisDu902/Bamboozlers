#pragma once

#include <lcom/lcf.h>
#include "rtc_macros.h"




int (rtc_subscribe_int)(uint8_t* bit_no);


int (rtc_unsubscribe_int)();


int (set_rtc_interrupt)( bool value);


int (wait_valid_rtc)();


void (rtc_ih)();


int (disable_update)();


int (enable_update)();


int (rtc_read_hours)(uint8_t reg, uint8_t* value);

void (rtc_upd)();

void (set_darkMode_alarm)();








