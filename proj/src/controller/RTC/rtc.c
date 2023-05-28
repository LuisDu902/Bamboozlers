#include "rtc.h"

int hook_rtc = 3;

uint8_t hour = 0, minute = 0, second = 0;


bool alarmInterrupt = false;
bool darkMode=false;

int (rtc_subscribe_int)(uint8_t *bit_no) {
  *bit_no=BIT(hook_rtc);
  return sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &hook_rtc);
}

int (rtc_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_rtc);
}

int (wait_until_finished_update)(){

  bool first = true;
  uint8_t reg;

  do{
      if(!first) tickdelay(micros_to_ticks(UPDATE_TIME_MICRO));
      if( OK != sys_outb(RTC_ADDR_REG,RTC_REG_A)) return !OK;
      if( OK != util_sys_inb(RTC_DATA_REG,&reg)) return !OK;
      first = false;
  }while(reg & RTC_UIP);

  return OK;
}

int enable_update(){
    uint8_t reg;
    if( OK != sys_outb(RTC_ADDR_REG,RTC_REG_B)) return !OK;
    if( OK != util_sys_inb(RTC_DATA_REG,&reg)) return !OK;
    reg = (reg & ~RTC_SET) | RTC_UIE;
    return sys_outb(RTC_DATA_REG,reg);
}

int disable_update(){
    uint8_t reg;
    if( OK != sys_outb(RTC_ADDR_REG,RTC_REG_B)) return !OK;
    if( OK != util_sys_inb(RTC_DATA_REG,&reg)) return !OK;
    reg |= RTC_SET;
    return sys_outb(RTC_DATA_REG,reg);
}

int set_rtc_interrupts(interruptType interrupt, bool value){
    uint8_t reg;
    sys_outb(RTC_ADDR_REG, RTC_REG_B);
    util_sys_inb(RTC_DATA_REG, &reg);
    switch(interrupt){
        case UPDATE:
            reg = value ? (RTC_UIE | reg) : (reg & (~RTC_UIE));
            break;
        case ALARM:
            reg = value ? (RTC_AIE | reg) : (reg & (~RTC_AIE));
            break;
        case PERIODIC:
            reg = value ? (RTC_PIE | reg) : (reg & (~RTC_PIE));
            break;
    }
    sys_outb(RTC_ADDR_REG, RTC_REG_B);
    sys_outb(RTC_DATA_REG, reg);
    return 0;
}

void (rtc_ih)(){
    uint8_t reg;
    sys_outb(RTC_ADDR_REG, RTC_REG_C);
    util_sys_inb(RTC_DATA_REG, &reg);

    if(reg & RTC_UF)
       rtc_updater();

    if(reg & RTC_AF)
        rtc_alarm();

    if(reg & RTC_PF)
        rtc_periodic();
}

int (rtc_read_info)(uint8_t reg, uint8_t* value){
    if(OK != wait_until_finished_update()){
        printf("Could not wait for the end of update!");
        return !OK;
    }
    if(OK != sys_outb(RTC_ADDR_REG, reg)){
        printf("Could not write to rtc's address register!");
        return !OK;
    }
    if( OK != util_sys_inb(RTC_DATA_REG, value)){
        printf("Could not read from rtc's data register!");
        return !OK;
    };

    return OK;
}

int (bcd_to_decimal)(uint8_t hex){
    if((((hex & 0xF0) >> 4) >= 10) || ((hex & 0x0F) >= 10)){
        printf("Invalid BCD value!");
        return !OK;
    }
    return ((hex & 0xF0) >> 4) * 10 + (hex & 0x0F);

}

int (decimal_to_bcd)(uint8_t dec){
    return ((dec%10)) | ((dec/10) << 4);
}

void set_power_up_alarm(){
    uint8_t hour_to_alarm;

    if(rtc_read_info(RTC_REG_HOUR, &hour_to_alarm)){
        printf("Could not read the second to alarm!");
    }

    if(hour >=19 || hour <6){
        hour_to_alarm=decimal_to_bcd(6);
        darkMode=true;
    }else{
        darkMode=false;
    }
    printf( "%d\n", minute);

    printf("%d\n", hour);

    printf("%d\n", second);

    sys_outb(RTC_ADDR_REG, RTC_REG_SEC_ALRM);
    sys_outb(RTC_DATA_REG, RTC_DONT_CARE);

    sys_outb(RTC_ADDR_REG, RTC_REG_MIN_ALRM);
    sys_outb(RTC_DATA_REG, RTC_DONT_CARE);

    sys_outb(RTC_ADDR_REG, RTC_REG_HOUR_ALRM);
    sys_outb(RTC_DATA_REG, hour_to_alarm);
}



void (rtc_updater)(){

    disable_update();

    if(rtc_read_info(RTC_REG_HOUR, &hour) || rtc_read_info(RTC_REG_MIN, &minute) || rtc_read_info(RTC_REG_SEC, &second)){
        printf("Could not update the time!");
    }


    hour = bcd_to_decimal(hour);
    minute = bcd_to_decimal(minute);
    second = bcd_to_decimal(second);

    enable_update();
}

void (rtc_alarm)(){
    set_power_up_alarm();
}

void (rtc_periodic)(){
}



uint8_t get_second(){
    rtc_read_info(RTC_REG_SEC, &second);
    second = bcd_to_decimal(second);
    return second;
}
