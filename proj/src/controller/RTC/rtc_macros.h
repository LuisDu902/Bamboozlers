#ifndef _LCOM_RTC_MACROS_H_
#define _LCOM_RTC_MACROS_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

#define RTC_IRQ 8

/* RTC I/O adreses */

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_SEC 0x00
#define RTC_REG_SEC_ALRM 0x01
#define RTC_REG_MIN 0x02
#define RTC_REG_MIN_ALRM 0x03
#define RTC_REG_HOUR 0x04
#define RTC_REG_HOUR_ALRM 0x05
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_C 0x0C
#define RTC_REG_D 0x0D

/* RTC REGISTER FLAGS */

#define RTC_UIP BIT(7)
#define RTC_SET BIT(7)
#define RTC_PIE BIT(6)
#define RTC_AIE BIT(5)
#define RTC_UIE BIT(4)
#define RTC_IRQF BIT(7)
#define RTC_AF BIT(5)
#define RTC_UF BIT(4)



#endif

