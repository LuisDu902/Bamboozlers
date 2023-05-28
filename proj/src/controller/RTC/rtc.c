#include <lcom/lcf.h>
#include "rtc.h"


typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} real_time_clock_info;
int hook_rtc = 5;
real_time_clock_info rtc_info;
bool Darkmode=false;
bool alarmInterrupt=false;


int (rtc_subscribe_int)(uint32_t *bit_no) {
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

int set_rtc_interrupt( bool value){
    uint8_t reg;
    sys_outb(RTC_ADDR_REG, RTC_REG_B);
    util_sys_inb(RTC_DATA_REG, &reg);

    reg = value ? (RTC_AIE | reg) : (reg & (~RTC_AIE));

    sys_outb(RTC_ADDR_REG, RTC_REG_B);
    sys_outb(RTC_DATA_REG, reg);
    return 0;
}
void set_darkMode_alarm(){
    uint8_t darkMode_alarm;

    if(rtc_read_info(RTC_REG_HOUR, &darkMode_alarm)){
        printf("Could not read the second to alarm!");
    }
    if(darkMode_alarm <6 || darkMode >19){
        darkMode_alarm=6;
        darkMode=true;
    }
    else {
        darkMode=false; 
        darkMode_alarm=20;
    }

    darkMode_alarm=decimal_to_bcd(darkMode_alarm);
    sys_outb(RTC_ADDR_REG, RTC_REG_SEC_ALRM);
    sys_outb(RTC_DATA_REG, RTC_DONT_CARE);

    sys_outb(RTC_ADDR_REG, RTC_REG_MIN_ALRM);
    sys_outb(RTC_DATA_REG, RTC_DONT_CARE);

    sys_outb(RTC_ADDR_REG, RTC_REG_HOUR_ALRM);
    sys_outb(RTC_DATA_REG, darkMode_alarm);
}

void (rtc_ih)(){
    uint8_t reg;
    sys_outb(RTC_ADDR_REG, RTC_REG_C);
    util_sys_inb(RTC_DATA_REG, &reg);

    if(reg & RTC_AF)
        rtc_alarm();

}
void (rtc_alarm)(){
    printf("alarm! ");
    alarmInterrupt = true;
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

void (rtc_updater)(){

    disable_update();

    if(rtc_read_info(RTC_REG_HOUR, &rtc_info.hour) || rtc_read_info(RTC_REG_MIN, &rtc_info.minute) || rtc_read_info(RTC_REG_SEC, &rtc_info.second)){
        printf("Could not update the time!");
    }

    enable_update();
}

int (decimal_to_bcd)(uint8_t dec){
    return ((dec%10)) | ((dec/10) << 4);
}


