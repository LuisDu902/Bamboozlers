
#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <lcom/lcf.h>
#include "rtc_macros.h"

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} real_time_clock_info;


void (rtc_setup)();
int (rtc_subscribe_interrupts)();
int (rtc_unsubscribe_interrupts)();
int (rtc_output)(uint8_t command, uint8_t *output);
int (rtc_is_updating)();
int (rtc_update_time)();


#endif

