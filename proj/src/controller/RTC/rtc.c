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

int (enable_update)(){
    uint8_t regB;
    if(sys_outb(ADDR_REG,REG_B) != 0) return 0;
    if(util_sys_inb(DATA_REG,&regB) != 0) return 0;
    regB = (regB & ~SET) | UIE;
    return sys_outb(DATA_REG,regB);
}

int (disable_update)(){
    uint8_t regB;
    if( sys_outb(ADDR_REG,REG_B) != 0) return 1;
    if( util_sys_inb(DATA_REG,&regB) != 0) return 1;
    regB |= SET;
    return sys_outb(DATA_REG,regB);
}


int (wait_valid_rtc)(){

  uint8_t regA=0;

  do{
      if(disable_update() != 0) return 1;
      if( 0 != sys_outb(ADDR_REG,REG_A)) return 1;
      if( 0 != util_sys_inb(DATA_REG,&regA)) return 1;
      if(enable_update() != 0) return 1;
  }while(regA & UIP);

  return 0;
}
void (rtc_ih)(){
    uint8_t regB;
    if(sys_outb(ADDR_REG, REG_C)!= 0) return ;
    if(util_sys_inb(DATA_REG, &regB) != 0) return ;

    if(regB & UF)
       rtc_upd();

    if(regB & AF)
        set_darkMode_alarm();

}

int (set_rtc_interrupt)(bool value){
    uint8_t regB;
    if(sys_outb(ADDR_REG, REG_B)!= 0) return 1;
    if(util_sys_inb(DATA_REG, &regB)!= 0) return 1;
    if(value){
        regB= (UIE | regB);
        regB= (AIE | regB);
    }
    else{
        regB= (regB & (~UIE));
        regB= (regB & (~AIE));;
    }

    if(sys_outb(ADDR_REG, REG_B) != 0) return 1;
    if( sys_outb(DATA_REG, regB) != 0) return 1;
    return 0;
}



int (rtc_read_hours)(uint8_t reg, uint8_t* hours){
    if(sys_outb(ADDR_REG, reg)!= 0){

        return 1;
    }
    if( 0 != util_sys_inb(DATA_REG, hours)){
        return 1;
    };

    return 0;
}
void (rtc_upd)(){

    disable_update();
    if( wait_valid_rtc() != 0){
        return ;
    }
    if(rtc_read_hours(REG_HOUR, &hour)){
        return ;
    }
    hour = ((hour & 0xF0) >> 4) * 10 + (hour & 0x0F);
    enable_update();
}
void (set_darkMode_alarm)(){
    uint8_t hour_alarm;
    if(wait_valid_rtc() != 0) return ;
    if(rtc_read_hours(REG_HOUR, &hour_alarm)){
        return;
    }

    if(hour >=20 || hour <6){
        hour_alarm=((hour%10)) | ((hour/10) << 4);
        darkMode=true;
    }else{
        darkMode=false;
        hour_alarm=((hour%10)) | ((hour/10) << 4);
    }

    if(sys_outb(ADDR_REG, REG_SEC_ALARM) != 0) return;
    if(sys_outb(DATA_REG, 0xFF) != 0) return;

    if(sys_outb(ADDR_REG, REG_MIN_ALARM) != 0) return;
    if(sys_outb(DATA_REG, 0xFF) != 0) return;

    if(sys_outb(ADDR_REG, REG_HOUR_ALARM)!= 0) return;
    if(sys_outb(DATA_REG, hour_alarm)!= 0)return;
}




