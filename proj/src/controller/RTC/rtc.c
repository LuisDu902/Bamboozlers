#include <lcom/lcf.h>
#include "rtc.h"


int rtc_hook_id = RTC_MASK; 
real_time_clock_info rtc_info;  
  

void (rtc_setup)() {
    rtc_update_time();
}

int (rtc_subscribe_interrupts)() {
    return sys_irqsetpolicy(IRQ_RTC, IRQ_REENABLE, &rtc_hook_id);
}


int (rtc_unsubscribe_interrupts)() {
    return sys_irqrmpolicy(&rtc_hook_id);
}


int (rtc_output)(uint8_t command, uint8_t *output) {
    if (sys_outb(IN_REG, command) != 0) return 1;
	if (util_sys_inb(OUT_REG, output) != 0) return 1;
    return 0;
}


int (rtc_is_updating)() {
    uint8_t result;
    if (rtc_output(REG_UPD, &result)) return 1;
	return result & UPD;
}

int (rtc_update_time)() {
    

    if (rtc_is_updating() != 0) return 1;
    uint8_t output;


    if (rtc_output(MINUTES, &output) != 0) return 1;
    rtc_info.minutes =  output ;


    if (rtc_output(HOURS, &output) != 0) return 1;
    rtc_info.hours =  output ;


    return 0;
}

