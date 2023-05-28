#include <lcom/lcf.h>
#include "rtc_macros.h"



int (rtc_subscribe_int)(uint32_t* bit_no);

int (rtc_unsubscribe_int)();


int set_rtc_interrupt( bool value);

int (wait_until_finished_update)();


void (rtc_ih)();


int disable_update();


int enable_update();


int (rtc_read_info)(uint8_t reg, uint8_t* value);


void (rtc_updater)();


void (rtc_alarm)();

int (decimal_to_bcd)(uint8_t dec);


