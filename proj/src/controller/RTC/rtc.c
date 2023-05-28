#include "rtc.h"

int hook_rtc = 3;

uint8_t hour = 0, minute = 0, second = 0;

bool darkMode=false;

int (rtc_subscribe_int)(uint8_t *bit_no) {
  *bit_no=BIT(hook_rtc);
  return sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &hook_rtc);
}

int (rtc_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_rtc);
}

int (wait_until_finished_update)(){


  uint8_t reg;

  do{
      if(disable_update() != 0) return 1;
      if( 0 != sys_outb(RTC_ADDR_REG,RTC_REG_A)) return 1;
      if( 0 != util_sys_inb(RTC_DATA_REG,&reg)) return 1;

  }while(reg & RTC_UIP);

  return 0;
}

int enable_update(){
    uint8_t reg;
    if( 0 != sys_outb(RTC_ADDR_REG,RTC_REG_B)) return 0;
    if( 0 != util_sys_inb(RTC_DATA_REG,&reg)) return 0;
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

int set_rtc_interrupts(bool value){
    uint8_t reg;
    sys_outb(RTC_ADDR_REG, RTC_REG_B);
    util_sys_inb(RTC_DATA_REG, &reg);

    reg = value ? (RTC_UIE | reg) : (reg & (~RTC_UIE));


    reg = value ? (RTC_AIE | reg) : (reg & (~RTC_AIE));


    
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
        set_darkMode_alarm();;

}

int (rtc_read_info)(uint8_t reg, uint8_t* value){
    if( wait_until_finished_update() != 0){
        return 1;
    }
    if(sys_outb(RTC_ADDR_REG, reg)!= 0){

        return 1;
    }
    if( 0 != util_sys_inb(RTC_DATA_REG, value)){
        return 1;
    };

    return 0;
}

int (bcd_to_decimal)(uint8_t hex){
    if((((hex & 0xF0) >> 4) >= 10) || ((hex & 0x0F) >= 10)){
        return !OK;
    }
    return ((hex & 0xF0) >> 4) * 10 + (hex & 0x0F);

}

int (decimal_to_bcd)(uint8_t dec){
    return ((dec%10)) | ((dec/10) << 4);
}

void set_darkMode_alarm(){
    uint8_t hour_to_alarm;

    if(rtc_read_info(RTC_REG_HOUR, &hour_to_alarm)){
        return;
    }

    if(hour >=20 || hour <6){
        hour_to_alarm=decimal_to_bcd(6);
        darkMode=true;
    }else{
        darkMode=false;
        hour_to_alarm=decimal_to_bcd(20);
    }

    sys_outb(RTC_ADDR_REG, RTC_REG_SEC_ALRM);
    sys_outb(RTC_DATA_REG, RTC_DONT_CARE);

    sys_outb(RTC_ADDR_REG, RTC_REG_MIN_ALRM);
    sys_outb(RTC_DATA_REG, RTC_DONT_CARE);

    sys_outb(RTC_ADDR_REG, RTC_REG_HOUR_ALRM);
    sys_outb(RTC_DATA_REG, hour_to_alarm);
}



void (rtc_upd)(){

    disable_update();

    if(rtc_read_info(RTC_REG_HOUR, &hour)){
        return ;
    }
    hour = bcd_to_decimal(hour);
    enable_update();
}
